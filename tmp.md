
```python
config.sampling_strategy = {'type':'multi_head',
        'num_classes': [487549,617412,209369,441462,602248,564463,637821],
                            'upsample_ratios': [1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0],
                            'sample_strategies': ['max20', 'max20', 'max20', 'max20', 'max20', 'max20', 'max20']
}

```

batch_size = 128
| Exp                         | 显存       | QPS |
| --------------------------- | ---------- | --- |
| base                        | 9800/11000 | 400 |
| deepspeed                   | 8400       | 400 |
| deepspeed+modify_init       | 8400       | 400 |
| deepspped+modify_init + cmd | 8400       | 400 |



多节点训练 8卡*2节点

| Exp     | batch_size | 显存        | QPS  |
| ------- | ---------- | ----------- | ---- |
| pytorch | 256        | 13530/16000 | 3900 |
| pytorch | 400        | 15550       | 4000 |

准备阶段：
1. docker内部需要通过`apt install`安装pdsh、ssh-server服务，如果不适用pdsh进行操控，也需要安装例如OpenMPI等。
2. pdsh要求`/usr/lib`的owner必须是命令的执行者或者是root，因此在docker内部需要修改为root。
3. 在`/etc/ssh/sshd-config`上修改ssh的端口为一个未被占用的端口，假定为P1，并且重启ssh服务,之前进行docker内部的ssh连接也可以使用这个方法。
4. 多个docker之前都要挂载/home目录，并且在这些机器之间需要建立master机器到其他节点的免密登录。
5. 需要切换到能够免密登录的用户运行deepspeed的启动命令，因为pdsh需要使用ssh连接。
6. 在正式运行deepspeed的命令之前可以使用`pdsh -w 'host1:P1,host2:P1' -R ssh 'nvidia-smi'`来检查是否能够正常连接（因为使用了非22端口，需要使用:P1来指定端口）。如果没有弹出`>pdsh`窗口，应该需要在docker内部使用`ssh-copy-id`做一些免密登录的事情。
7. 需要一个hostfile.txt文件，里面的内容格式为若干行`IP或者hostname slots=调用显卡数量`，这里的slot应该要大于等于之后通过deepspeed命令行--num_gpus指定的显卡数量，最终启动的显卡数量还是由--num_gpus指定。
8. 修改train_v2.py,deepspeed要求代码能够接受一个--local_rank的参数，并且将这个参数作为local_rank.
9. 通过命令`deepspeed --ssh_port 8022  --num_gpus=8 --num_nodes=2  --hostfile=hostfile.txt --master_port=${DISTRIBUTED_MASTER_PORT} --master_addr="${DISTRIBUTED_MASTER_ADDR}"  train_v2.py configs/deepspeed.py`进行启动，尤其要注意--ssh_port参数需要设置为docker内部的端口，不设置会连接到外部的机器。deepspeed的命令是通过launcher进行启动的，详细资料可以参考[这个](https://github.com/microsoft/DeepSpeed/blob/6763e2de610b006c0fafc2c19a31f6508c920d1b/deepspeed/launcher/launch.py)


一些实验过程中的经验：

1. 大部分网上公开的代码使用init_distributed函数都是直接指定nccl即可，但是这对于我们的实验这样做会直接卡住。
2. deepspeed.comm完全基于torch.distributed进行封装，不会影响性能。
3. 目前主要是deepspeed的launch逻辑和torchrun不一致，并且deepspeed启动命令会严重影响实验的速度。
4. deepspeed除了pdsh可以进行多节点的启动以外，还可以使用OpenMPI等一些其他的库来进行启动，略微尝试过OpenMPI，仍然没有太多改善。
5. 之前尝试过使用docker的-p命令将外部的其他端口映射到内部的ssh的22号端口，这样会导致程序卡在init阶段，我认为这是使用-p命令导致docker内部的端口没有暴露出去，从而导致torch进行显卡通信等接口没有联通，从而一直在进行等待。因此在docker内部，网络通信的当时还是采用host，如何有对docker更加理解的，或许可以采用桥接的方式来进行通信，从而不必进行ssh的设置，直接进行连接，这样自动化更强一些。