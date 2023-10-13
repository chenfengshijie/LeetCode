- [简介](#简介)
  - [Prompt设计](#prompt设计)
    - [hand-crafted prompt](#hand-crafted-prompt)
    - [Continuous prompt](#continuous-prompt)
  - [参考文献](#参考文献)


在最开始，介绍两个长期跟踪prompt工作的网站：
- [github prompt paper](https://github.com/thunlp/PromptPapers)
- [pretrain prompt predict](http://pretrain.nlpedia.ai/)
# 简介

深度学习中的Prompt：引领NLP的第四范式

自2021年大模型的兴起以来，prompt作为一种重要的模型输入调整手段，逐渐得到了广泛的关注和研究。在刘鹏飞的关于NLP prompt的综述[^1]中，甚至将其视为NLP领域的第四范式，标志着其在自然语言处理中的重要性。随着大模型的不断进展，对于大模型中prompt的研究也在不断地深入，推动着NLP领域的发展。

![trend](https://img2023.cnblogs.com/blog/3183309/202309/3183309-20230920114114973-2047020025.png)

Prompt与Fine-tune的共同目标在于将预训练模型和下游任务（在计算机视觉领域，如目标检测、图像生成等）的输入输出尽可能地相近。回顾一下Fine-tune的做法，通常需要在一个在ImageNet-1k上验证过的模型骨架（backbone）上添加一系列组件，例如RPN网络和ROIHead，最后再加入一个分类器。此外，Fine-tune会对该骨干模型进行一些`loss func`和`optimizer`的调整，以及引入下游任务的一些先验信息（例如，目标检测需要引入检测框的位置信息）。然而，在Fine-tune过程中，通常不会对输入数据进行太多修改，而是希望通过训练使骨干模型能够蕴含更多有关下游任务的信息。

与此相反，Prompt的核心在于修改输入数据，以使下游任务的输入和输出更贴近骨干模型，而不是为骨干模型提供更多下游信息的知识。因此，使用Prompt的前提是模型必须具备充足的相关知识，以便接受修改下游任务输入和输出的操作，以与模型相匹配。根据综述[^1]的定义，Prompt的主要构成包括：

1. **Prompt Engineering**：定义一个函数 $f_{prompt}$，将下游任务的输入 $x$ 转化为骨干模型的输入 $x'$。
2. **选择合适的模型骨干**：确定适合的模型骨干，并将 $x'$ 输入该骨干以获取输出 $y$。
3. **Answer Engineering**：定义一个函数 $g_{prompt}$，将骨干模型的输出 $y$ 转化为下游任务的输出 $y'$。

多模态任务中的prompt学习是一种利用预训练模型的语义表示能力，通过构造合适的输入文本和输出文本，来完成不同下游任务的方法。这种方法不需要对预训练模型进行大规模的微调，而是通过简单而有效的文本提示，来激活预训练模型中与目标任务相关的知识和能力。多模态任务中的prompt学习主要涉及以下几个方面：

1. 预训练模型的选择。预训练模型是prompt学习的基础，不同的预训练模型具有不同的特点和优势。目前，多模态领域中常用的预训练模型可以分为两类：
    - 判别式的预训练模型，如CLIP，它使用对比学习的方式，在大规模的图像-文本对上进行预训练，学习图像和文本之间的语义对齐。这类模型适合于处理分类、检索等判别性任务，如果需要用在生成方面需要额外添加decoder模型并进行训练。
    - 生成式的预训练模型，如VLP，它使用遮盖语言建模（MLM）和图像-文本匹配（ITM）的方式，在大规模的图像-文本对上进行预训练，学习图像和文本之间的语义关联。这类模型适合于处理描述、问答等生成性任务，但对比能力较差。


2. Prompt Engineering，即prompt的设计。prompt是指输入到预训练模型中的文本部分，它通常包含一个或多个遮盖符号（mask），用于提示预训练模型在给定图像或文本条件下，生成或预测与目标任务相关的输出。prompt的设计方法可以分为以下几种：
    - Hand-crafted，即手工设计。这种方法根据每个特定下游任务的特点和需求，人为地构造一个固定的文本模板，作为输入到预训练模型中的prompt。这种方法简单直观，但需要专业知识和经验，并且缺乏泛化能力。
    - Discrete，即离散化。这种方法将输入映射到一个离散的空间中，例如使用词嵌入或字符嵌入来表示输入。这种方法可以增加prompt的可解释性和灵活性，但也增加了优化难度和计算开销，并且在自然语言处理（NLP）领域已经被证明表现不如其他方法。
    - Continuous，即连续化。这种方法将输入映射到一个连续的空间中，例如使用向量或张量来表示输入。这种方法可以充分利用预训练模型的语义表示能力，并且不需要为每个下游任务设计一个固定的文本模板。但是，这种方法也存在一些挑战，例如如何设计一个具有强泛化能力和鲁棒性的连续prompt。


3. Answer Engineering，即输出重构。输出重构是指将预训练模型生成或预测出来的输出文本，转换成与下游任务相符合的形式。例如，在分类任务中，输出重构可以将输出文本映射到类别标签；在检索任务中，输出重构可以将输出文本转换成相似度得分；在生成任务中，输出重构可以将输出文本进行后处理或重排等操作。由于多模态领域中的大多数任务都可以很自然地使用文本标签来表示输出，因此关于输出重构的研究相对较少。


4. Multi-prompt，即多prompt融合。多prompt融合是指使用多个不同的prompt来处理同一个下游任务，并将它们的输出进行融合或集成，以提高最终的效果。这种方法可以利用不同prompt之间的互补性和多样性，增加模型的鲁棒性和泛化能力。目前，这个方向在多模态领域中的研究还比较少，需要进一步探索。


5. prompt范式下的训练策略。训练策略是指在使用prompt进行下游任务时，如何对预训练模型和prompt进行优化和调整。训练策略主要涉及以下几个方面：
    - 模型是否微调。由于多模态预训练模型通常具有很大的规模和复杂度，因此直接对整个模型进行微调是不可行或不经济的。因此，大部分prompt学习的方法都是不对预训练模型进行微调的，而是只对其中一部分进行修改或适应，例如图像编码器或文本解码器等。
    - prompt是否具备额外参数。一些prompt学习的方法会为prompt引入一些额外的参数，例如嵌入向量或权重矩阵等，以增加prompt的表达能力和灵活性。这些参数可以与预训练模型一起进行优化，也可以单独进行优化。
    - 是否添加额外的网络架构。一些prompt学习的方法会在预训练模型的基础上，添加一些额外的网络架构，例如transformer或者decoder等，以增强预训练模型和prompt之间的交互和融合。这些网络架构可以作为一个中间层或一个输出层，也可以与预训练模型一起进行优化。


目前prompt的工作主要集中于NLP方面，特别是GPT一类的语言大模型（LLM）。针对多模态领域的prompt工作则相对较少，并且大部分工作尝试将NLP领域的一些trick迁移到多模态中来。并且多模态的prompt相关的论文还没有一个系统的综述，因此我大致按照时间顺序来对多模态的prompt进行介绍。

## Prompt设计

### hand-crafted prompt
CLIP: Learning Transferable Visual Models From Natural Language Supervision,[code](https://github.com/openai/CLIP)

CLIP是一种利用对比学习的方式，在大规模的图像-文本对上进行预训练的模型，它可以学习图像和文本之间的语义对齐，并且具有很强的零样本学习能力。CLIP在使用预训练模型进行图像分类任务时，采用了一种基于prompt的方法，而不是传统的微调方法。具体来说，CLIP使用了以下几个步骤：

1. 对于每个待分类的图像，CLIP使用预训练的图像编码器（Image-Encoder）提取其特征向量。
2. 对于每个可能的类别标签，CLIP构造一个固定的文本模板，形式为`A photo of X`，其中`X`是类别名称。例如，如果类别是猫，那么文本模板就是`A photo of a cat`。然后，CLIP使用预训练的文本编码器（Text-Encoder）提取其特征向量。
3. 对于每个图像-文本对，CLIP计算它们之间的余弦相似度，作为它们之间的语义匹配程度。
4. 对于每个待分类的图像，CLIP选择与其特征向量最相似的文本模板对应的类别标签，作为其分类结果。

![CLIP](https://img2023.cnblogs.com/blog/3183309/202309/3183309-20230919131922461-103141737.png)

这种基于prompt的方法与传统的微调方法有明显的区别。传统的微调方法通常需要在预训练模型的图像编码器后面添加一个全连接层（FC），作为分类器，并且在一些有标注数据的下游数据集上对FC层进行训练，然后用于分类任务。这种方法需要额外的数据和计算资源，并且可能导致预训练模型与下游任务之间的不匹配，并且往往会在zero-shot或者few-shot任务上导致过拟合现象。

而CLIP[^3]使用了一种简单而有效的prompt技巧，即`A photo of X`，来激活预训练模型中与目标任务相关的知识和能力，并且不需要对预训练模型进行任何修改或微调。这种方法可以充分利用预训练模型在大规模数据上学习到的通用和丰富的语义表示，并且具有很强的泛化能力和鲁棒性。实验结果也表明，这种基于prompt的方法在零样本学习场景下，可以显著优于传统的微调方法。

### Continuous prompt

[CoOp Code](https://github.com/KaiyangZhou/CoOp)
[CoCoOp Code](https://github.com/thunderenlight/cocoop)
**分类**：CoOp的作者在对CLIP的prompt进行实验的时候发现，对于同一张图片，不同的自然语言描述会导致不同的分类结果。例如一张猫的图片，可以有多种不同的prompt，如`a photo of cat`, `a cat`,`a class of cat`。这些prompt在CLIP中对应不同的类别向量，从而影响了分类性能。为了解决这个问题，CoOp提出了一种上下文优化（Context Optimization）的方法，将NLP中的连续prompt（continuous prompt）的方法引入到多模态的prompt中来，摒弃了为每个下游任务设计固定模板（template）的方法。

![img](https://img2023.cnblogs.com/blog/3183309/202309/3183309-20230920125639002-1721757103.png)

如图所示，CoOp[^4]将每个类别对应的prompt分为两部分：一个是固定的上下文（context），一个是可学习的嵌入（embedding）。上下文是一个自然语言描述，用于输入的类别，例如`cat`。可学习的嵌入是一个可学习的参数。这两部分通过线性变换和归一化后拼接在一起，形成最终的prompt向量。CoOp通过优化一个对比损失函数（contrastive loss function），使得同类别的图片和prompt向量之间的相似度更高，而不同类别之间的相似度更低。

这篇论文还尝试了其他的嵌入类别信息的方式，例如将类别嵌入到可学习的上下文中，或者为每一个类别设计单独的可学习的上下文。最终得出结论，对于细粒度（fine-grained）的分类任务，单独设计上下文的效果更好，而对于粗粒度（coarse-grained）的分类任务，所有类别共享上下文的效果更好。

CoOp是第一篇将NLP中的prompt方法引入到多模态的prompt中来的论文。它采用的prompt方法也证实了prompt能够取得相比于预训练（pretrain）更好的性能。但它采用的手动设计上下文方法是很不严谨的，这也潜在地证明了prompt有更大的潜力。

CoCoOp[^6]是该团队在CoOp的基础上提出的一种条件式prompt（conditional prompt）的方法。CoOp在训练时只考虑了文本特征，而没有关注视觉特征，这就导致它在进行零样本（zero-shot）或者少样本（few-shot）任务时候过拟合。CoCoOp希望解决可学习向量在陌生类别上泛化能力弱（generalization ability）的问题。cocoop论文额外添加了一个元网络（meta-net），将图像编码器（image-encoder）产生的视觉特征通过元网络融合（直接相加）到可学习向量中。

![img](https://img2023.cnblogs.com/blog/3183309/202309/3183309-20230920162215580-2093714986.png)

如图所示，元网络其实就是两层全连接层映射。添加元网络之后，CoCoOp在陌生类别上的效果比CoOp更好一些，但是基类上（base class）上的效果比CoOp要差一些。这说明CoCoOp解决了CoOp的过拟合问题，提高了prompt的泛化能力。但是，这个设置也降低了对于熟悉图像的处理能力，可能需要进一步的平衡。

[DenseCLIP Code](https://github.com/raoyongming/DenseCLIP)

**Dense Prediction**：DenseCLIP[^5]是一种将prompt的方法用于像素级别的密集预测任务上的框架。CLIP是一种利用对比学习的方法进行视觉-语言预训练的模型，但是CLIP的训练和预测都是在实例级别(instance-level)进行的，无法直接应用到像素级别(pixel-level)的任务上，如语义分割、目标检测和实例分割等。DenseCLIP通过微调一个图像解码器(Image-Decoder)，并将视觉的特征经过一个变换器(transformer)注入到文本特征中，并将视觉特征和文本特征进行比对，得到一个像素-文本匹配得分图(pixel-text score map)。然后将这个得分图输入到图像解码器做下游像素级别的任务，并使用对应的损失函数(loss)来进行训练。

![img](https://img2023.cnblogs.com/blog/3183309/202309/3183309-20230920150417845-1803285538.png)

DenseCLIP还提出了一个预提示(pre-prompt)的方式，直接将视觉特征融合到提示(prompt)中，然后通过文本编码器(text encoder)生成类别嵌入(class embedding)。

![img](https://img2023.cnblogs.com/blog/3183309/202309/3183309-20230920151111810-2009146346.png)

DenseCLIP将CLIP prompt应用到了像素相关的任务上，证明了prompt在密集预测任务上的巨大潜力。CLIP之所以很难用于密集的预测任务，这主要是因为CLIP的训练都是在实例级别(instance-level)，无论是图片还是文本都是实例级别的粗粒度(granularity)。但是DenseCLIP在整个CLIP中只固定text encoder，需要训练image encoder和设计的image decoder；这其实需要更多的数据来进行训练。此外，DenseCLIP还需要设计合适的提示(prompt)，以及考虑如何平衡提示和视觉特征之间的权重。

[Code](https://github.com/j-min/VL-T5)

**统一的Prompt**:在视觉和语言的任务中，通常需要为每一个下游任务设计特定的模型结构和目标函数，例如，为了解决视觉问答（VQA）问题，需要构建一个多标签分类器，为了解决指代表达理解（Referring Expression Comprehension, REC）问题，需要构建一个区域打分器，为了解决图像描述（Image Captioning）问题，需要构建一个语言生成器，等等。这些方法不仅增加了模型的复杂度和开发成本，而且也限制了模型在不同任务之间共享和迁移知识的能力。为了克服这些困难，这篇论文[^7]提出了一个统一的框架，基于编码器-解码器（Encoder-Decoder）模型，使用相同的语言建模目标，即多模态条件文本生成（Multimodal Conditional Text Generation），来学习不同的视觉和语言任务。该框架可以同时处理VQA、REC、视觉常识推理（Visual Commonsense Reasoning, VCR）等7个下游任务，并且只需要在输入和输出上进行简单的适配。本文的主要贡献是将多种视觉和语言任务统一为文本生成问题，并且证明了这种方法在性能和泛化能力上与最先进的任务特定模型相当。

![img](https://img2023.cnblogs.com/blog/3183309/202309/3183309-20230921221852819-2013745469.png)

对于模型的输入输出设计，本文采用了类似于T5的方法，即在输入序列的开头添加一个表示任务类型的token，如`<VQA>`、`<REC>`等，并且使用特殊的token来标记文本和图像中被遮盖（mask）的部分，如`<vis1>`、`<text1>`等。这些token可以帮助模型区分不同的输入模态和任务需求，并且可以通过预训练和微调来学习它们的语义。对于输出序列，本文根据不同任务的输出格式来生成相应的文本标签。例如，对于REC任务，输出序列会是`<vis1>`表示被指代的区域；对于VQA任务，输出序列会是一个或多个单词表示答案；对于图像描述任务，输出序列会是一个完整的句子描述图像内容。


[OFA Code](https://github.com/OFA-Sys/OFA)


在深度学习领域，不同的任务和模态通常需要不同的模型架构和训练方法，这导致了大量的工程复杂度和资源浪费。为了解决这个问题，一些研究者尝试设计一个统一的框架，可以同时处理多种任务和模态，而无需对每个任务进行专门的定制。这样的框架通常基于prompt的思想，即将任务的输入和输出都表示为token序列，并使用一个具有足够容量的预训练模型来生成或预测输出序列，然而之前很少有研究在多个不同下游任务的数据集上训练一个模型，大部分都是基于预训练模型进行prefix-tune或者prompt。

2022年，阿里达摩院的王鹏等人提出了一个名为OFA（one for all）的框架[^10]，它是目前最先进的多模态预训练框架之一。虽然OFA并不是在已有的预训练模型上进行研究工作的，但它也可以看作是一种prompt的工作，因为它将所有的下游任务都建模为seq2seq任务，并使用一个统一的模型来处理不同的输入和输出。OFA支持多种跨模态和单模态的任务，包括图像生成、视觉定位、图像描述、图像分类、语言建模等。OFA遵循基于指令的学习，在预训练和微调阶段都不需要额外的任务特定层。例如，实体检测的输出会被转化为`<loc x1>,<loc x2>...`，而对于模型内部使用的backbone仍然是老一套的transformer和resnet。OFA只使用了2000万公开可用的图像-文本对进行预训练，但在一系列跨模态任务上达到了新的SOTA水平，在单模态任务上也表现出了高度竞争力。OFA还能有效地迁移到未见过的任务和领域。

![img](https://img2023.cnblogs.com/blog/3183309/202309/3183309-20230921222651396-1522268963.png)

**LM->MultiModel**(代码未开源):多模态任务通常需要一个预训练的多模态模型来进行微调或适应，但是这篇论文[^8]提出了一种利用语言模型（language model, LM）来进行提示（prompt）的方法，从而实现多模态的少样本学习（few-shot learning）。它的思想是用一个图像编码器（image encoder）将图像转换为一系列的连续嵌入（continuous embeddings），作为LM的输入前缀（prefix），与文本一起送入LM中，从而激活LM中的先验知识（prior knowledge）。为了避免LM在多模态领域过拟合或遗忘，作者选择在训练时固定LM的参数（frozen），只优化图像编码器相关的参数。图像前缀的构造方式如下图所示：将图像编码器的输出映射为D*n的矩阵，其中D为嵌入维度，n为嵌入的token数量。

![img](https://img2023.cnblogs.com/blog/3183309/202309/3183309-20230920231511586-192977427.png)

由于该方法只使用少量或零样本（zero-shot）来进行多模态任务，因此不能对LM进行微调（fine-tuning），否则会导致LM产生灾难性遗忘（catastrophic forgetting）。该方法的优点是模型结构简单，训练过程容易，并且不需要微调LM，因此是一个轻量级的提示工作。但是它的性能也比较一般，达不到最先进（state-of-the-art, SOTA）的水平。

![img](https://img2023.cnblogs.com/blog/3183309/202309/3183309-20230920231511586-192977427.png)

需要注意的是，由于few-shot或者zero-shot的样本数量较少，所以该模型不能够对LM进行微调，LM的参数是固定的，只优化图像编码器的参数。否则就是使得LM产生灾难性遗忘。本文的模型较为简单，训练也十分容易，并且不用微调LM，因此是一个轻量级的prompt工作，他的性能也比较一般，达不到sota的水平。

[CPT Code](https://github.com/thunlp/CPT)
**visual grounding**:CPT[^2]是一种基于预训练视觉-语言模型 (VL-PTMs) 的跨模态Prompt-Tuning方法，它利用颜色作为图像和文本之间的共指标记，将视觉基础问题转化为填空问题。具体来说，它将输入图片中的物体替换为不同的颜色，并在文本描述中添加相应颜色的mask作为提示。例如，对于图片中的“黄色人”，它会生成“[MASK] person”作为文本提示，并要求模型预测出正确的颜色。这样做可以最大程度地缩小预训练和微调之间的目标形式差距，从而提高VL-PTMs在视觉基础任务上的泛化能力。这种方法与手工设计的prompt有些相似，因为它不涉及任何参数更新，只依赖于模型对文本和视觉特征之间关系的理解。

CPT是一种非常轻量级和灵活的prompt方法，几乎可以看作是手工设计的prompt的一种自动化版本。它在多种视觉基础任务上都取得了优异的性能，包括实体检测、场景图分类、视觉常识推理等。与传统的微调方法相比，CPT不需要大量标注数据或计算资源，甚至可以在零样本或少样本条件下实现有效的视觉基础。CPT背后的思想其实就是利用prompt将视觉基础问题转化为模型内部已经掌握的选择题问题，从而激发出VL-PTMs潜在的跨模态能力。

![img](https://img2023.cnblogs.com/blog/3183309/202309/3183309-20230921185213511-1585589343.png)



## 参考文献

[^1]:《Pre-train, Prompt, and Predict: A Systematic Survey of Prompting Methods in Natural Language Processing》
[^2]:CPT: Colorful Prompt Tuning for Pre-trained Vision-Language Models
[^3]:CLIP: Learning Transferable Visual Models From Natural Language Supervision.
[^4]:CoOp: Learning to Prompt for vision-language models CVPR 2021.9
[^5]:DenseCLIP: Language-Guided Dense Prediction with Context-Aware Prompting (2021.12)
[^6]:CoCoOp: Conditional Prompt Learning for Vision-Language Models CVPR 2022
[^7]:Unifying Vision-and-Language Tasks via Text Generation ICML 2021
[^8]:Multimodal Few-Shot Learning with Frozen Language Models NIPS 2021
[^9]:
[^10]:Unifying Architectures,Tasks,and Modalities Through a Simple Sequence-to-Sequence Learning Framework 2022