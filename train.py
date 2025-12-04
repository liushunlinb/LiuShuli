import os
# os.environ['TF_ENABLE_ONEDNN_OPTS'] = '0'  # 需在导入 TensorFlow/PyTorch 前设置
import torch
import torchvision.datasets
from PIL.Image import Image
from torch import nn
from torch.nn import functional as F
from torch.nn import Sequential, Conv2d, MaxPool2d, Linear, Flatten
from torch.utils.data import DataLoader
from torch.utils.tensorboard import SummaryWriter
from torchvision.datasets import ImageFolder
from torchvision import transforms

# 定义训练集和验证集的不同预处理
train_transform = transforms.Compose([
    transforms.Resize((224,224)),  # 调整尺寸
    transforms.RandomHorizontalFlip(p=0.5),
    transforms.RandomVerticalFlip(p=0.3),  # 垂直翻转
    transforms.RandomRotation(30),  # 大角度旋转
    transforms.ColorJitter(brightness=0.4,  # 增强颜色变化
                           contrast=0.3,
                           saturation=0.3,
                           hue=0.1),
    transforms.RandomAffine(degrees=0, shear=10),  # 仿射变换
    transforms.RandomPerspective(distortion_scale=0.3, p=0.5),  # 透视变换
    # transforms.CutMix(p=0.5, alpha=0.3)  # 调整alpha控制混合强度
    transforms.ToTensor(),
    transforms.Normalize(mean=[0.485, 0.456, 0.406],
                         std=[0.229, 0.224, 0.225]),
    transforms.RandomErasing(p=0.5, scale=(0.02, 0.2)),  # 随机擦除

])
test_transform = transforms.Compose([
    transforms.Resize((224, 224)),                  # 固定缩放
    transforms.ToTensor(),
    transforms.Normalize([0.485, 0.456, 0.406], [0.229, 0.224, 0.225])
])
scaler = torch.amp.GradScaler('cuda')
tudui = torch.load("fruits1_4.pth")
if __name__ == '__main__':
    train_data = ImageFolder(root="Fruits1/train/", transform=train_transform)
    train_Dataloader = DataLoader(train_data, batch_size=128, shuffle=True, num_workers=3 ,pin_memory=True, prefetch_factor=2)
    test_data = ImageFolder(root="Fruits1/test/", transform=test_transform)
    test_Dataloader = DataLoader(test_data, batch_size=128, shuffle=True,pin_memory=True)

    train_data_size = len(train_data)
    test_data_size = len(test_data)

    print("训练数据集的长度为：{}".format(train_data_size))
    print("测试训练数据集的长度为：{}".format(test_data_size))

    num_classes = len(train_data.classes)
    # tudui = torchvision.models.GoogLeNet(num_classes)
    # tudui = torchvision.models.vgg16(weights=False)
    # tudui.classifier[6] = Linear(4096, 131)
    # print(num_classes)
    input_shape = (3, 224, 224)
    # tudui = CNN(input_shape, num_classes)
    # tudui = torchvision.models.resnet34(weights=torchvision.models.ResNet34_Weights.IMAGENET1K_V1) #加载网络模型并加载预训练权重
    # tudui.fc = torch.nn.Linear(tudui.fc.in_features, num_classes) #修改最后一层全连接层
    # tudui = torchvision.models.resnet50(weights=torchvision.models.ResNeXt50_32X4D_Weights)
    # tudui.fc = torch.nn.Linear(tudui.fc.in_features, num_classes)  # 修改最后一层全连接层
    # tudui = torchvision.models.efficientnet_b4(weights=torchvision.models.efficientnet_b4)
    tudui = tudui.cuda() #开启cuda训练
    loss_fn = nn.CrossEntropyLoss() #使用交叉信息熵
    loss_fn = loss_fn.cuda()
    # optim = torch.optim.SGD(tudui.parameters(), lr=0.01)
    # optim = torch.optim.Adam(tudui.parameters(), lr=0.01)
    # optim = torch.optim.Adam(tudui.parameters(), lr=0.0003, weight_decay=1e-4)
    optim = torch.optim.AdamW(tudui.parameters(), lr=0.000002, weight_decay=1e-4) #设置优化器和权重衰减
    scheduler = torch.optim.lr_scheduler.CosineAnnealingLR(optim, T_max=50)  #设置学习率调整方式为余弦退火

    # scheduler = torch.optim.lr_scheduler.ReduceLROnPlateau(optim, 'min', patience=10, min_lr=1e-6)
    total_train_step = 0
    total_test_step = 0
    epoch = 100 #设置训练轮数

    writer = SummaryWriter("logs_train")

    for i in range(epoch):
        print("-------------第 {} 轮训练开始-----------".format(i + 1))
        for data in train_Dataloader:
            imgs, targets = data
            imgs = imgs.cuda()
            targets = targets.cuda()
            optim.zero_grad()
            with torch.amp.autocast('cuda'):
                outputs = tudui(imgs)
                loss = loss_fn(outputs, targets)
            scaler.scale(loss).backward()
            scaler.step(optim)
            scaler.update()
            total_train_step = total_train_step + 1
            if total_train_step % 100 == 0:
                #print("训练次数：{}, Loss:{}".format(total_train_step, loss))
                writer.add_scalar("train_loss", loss, total_train_step)

        total_loss = 0
        total_accuracy = 0
        with torch.no_grad():
            for data in test_Dataloader:
                imgs, targets = data
                imgs = imgs.cuda()
                targets = targets.cuda()
                outputs = tudui(imgs)
                loss = loss_fn(outputs, targets)
                total_loss = total_loss + loss
                accuracy = (outputs.argmax(1) == targets).sum()
                total_accuracy = total_accuracy + accuracy
        print("整体测试集上的Loss：{}".format(total_loss))
        print("整体测试集上的正确率：{}".format(total_accuracy / test_data_size))
        writer.add_scalar("test_loss", total_loss, total_test_step)
        writer.add_scalar("test_accuracy", total_accuracy/test_data_size, total_test_step)
        total_test_step = total_test_step + 1
        torch.save(tudui, "fruits1_{}.pth".format(i))
        print("模型已保存")

    writer.close()
