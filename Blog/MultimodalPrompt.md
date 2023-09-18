# 简介

prompt在自2021年大模型的兴起之后，逐渐得到了广泛的关注和研究.Pre-train, Prompt, and Predict在刘鹏飞的关于NLP prompt综述[^1]内甚至被成为NLP的第四范式。

prompt类似于fine-tune，他们的共同目标都是使得预训练模型和下游任务（在CV方向就是目标检测、图像生成等）尽可能地相近。回忆起在fine-tune预训练模型地做法，我们往往在一个已经在ImageNet-1k上的得到验证的模型backbone，如果想要使用这个模型来做目标检测，我们需要在backbone上添加一个RPN网络，然后再添加一个ROIHead，最后再添加一个分类器，然后对这个backbone做一些`loss func`、`optimizer`的修改，引入下游任务的一些先验的信息（如目标检测就引入一些检测框的位置信息）。在进行fine-tune时候，一般不会对输入数据做任何的修改，我们只希望backbone模型通过训练，能够蕴含更多的下游任务的信息。

而prompt则刚好相反，关于prompt的工作则大部分集中于对于输入数据的修改，prompt通过在数据的输入和输出进行修改，使得下游任务的输入和输出更加靠近backbone，而不是使得backbone具备更多下游信息的知识。

[x]：# (2021-08-10 21:55:00)
[]:asdfasdf

## 参考文献

[^1]pengfeiLiu （2021）《Pre-train, Prompt, and Predict: A Systematic Survey of Prompting Methods in Natural Language Processing》