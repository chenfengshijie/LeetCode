# Swin transformer: Hierarchical Vision Transformer using Shifted Windows

**ICCV2021**
## 针对的问题

1. ViT论文发表证明了transformer可以用于cv任务，当还没有一个通用的骨干网络backbone能够通用语所有的cv任务，本文设计的swin transformer在cv的所有下游mlp任务上获得了成功，能够取代CNN成为CV的通用方法。
2. 目前将transformer用于cv视觉任务仍然具有以下难点：
    - 目前CV的输入往往远大于NLP的单词序列，ViT将图片分为多个Patch可以解决分类任务，当CV的一些任务需要像素级别的输出的时候就无法使用Patch方法。CNN对于这种像素级别的输出采用了金字塔或者U-Net等方式来进行多尺度的特征分析，而ViT中并没有进行多尺度的分析。
    - ViT的模型大小是随着输入的Token序列呈现二次增长，这限制了模型的输入尺寸。

针对上述的两个问题，Swin transformer主要提出了一个滑动窗口的机制，来解决多尺度的问题，并将模型的大小随着输入尺寸得到了线性的增长，从而能够很好地解决CV的绝大部分下游任务，成为一个通用的backbone。

## Related Work

### CNN-based

transformer出来之后，CNN方面采取了主要是两个方向：
- 在局部做self-attention，得到之后的输出做CNN。
- 使用CNN得到特征图feature map,在特征图上做self-attention

### Transformer-based

目前ViT模型对于输入的Token序列长度成二次曲线增长，并且需要更大的数据集来进行训练。DeiT（基于知识蒸馏的模型）证明了transfomer模型在同样的数据集上也能够达到和CNN同样的性能。

## Method

1. 局部窗口的self-attention，Swin transformer能够生成不同尺度上的特征图，可以供下游的任务来进行推理。

<img src="https://img2023.cnblogs.com/blog/3183309/202308/3183309-20230826140717256-1533280834.png" alt="image">

2. Shifted window.在上述经过MSA得到的特征图之后，还有经过一层SMSA，它通过cycle-move然后设计掩码来进行实现，相比于滑动窗口而言能够得到更好的结果。

![shift window](https://img2023.cnblogs.com/blog/3183309/202308/3183309-20230826145542556-815859974.png)

SMSA的掩码：
![mask](https://img2023.cnblogs.com/blog/3183309/202308/3183309-20230826145854808-1566028020.png)

3. 相对位置编码，在进行self-attention的时候，模型无法知道当前处理的是第几个patch，所以加入了一个相对的位置偏置，这个位置偏置对于模型来说很重要，在后面的消融实验表明大概能够上升2%的AP。

$\operatorname{Attention}(Q,K,V)=\operatorname{SoftMax}(QK^T/\sqrt d+B)V,$

    如果将相对位置编码换成绝对位置编码，会降低模型的性能。

总的模型图：

![img](https://img2023.cnblogs.com/blog/3183309/202308/3183309-20230826153112073-1653367438.png)


对于每一个Swin Block中的forward过程：

$$
\begin{aligned}
&\hat{\mathbf{z}}^l=\text{W-MSA }\left(\mathrm{LN}\left(\mathbf{z}^{l-1}\right)\right)+\mathbf{z}^{l-1}, \\
&\mathbf{z}^l=\text{М}\mathrm{LP}\left(\mathrm{LN}\left(\hat{\mathbf{z}}^l\right)\right)+\hat{\mathbf{z}}^l, \\
&\hat{\mathbf{z}}^{l+1}=\text{SW-MSA}\left(\mathrm{LN}\left(\mathbf{z}^l\right)\right)+\mathbf{z}^l, \\
&\mathbf{z}^{l+1}=\text{МLР}\left(\text{LN}\left(\hat{\mathbf{z}}^{l+1}\right)\right)+\hat{\mathbf{z}}^{l+1},
\end{aligned}
$$
