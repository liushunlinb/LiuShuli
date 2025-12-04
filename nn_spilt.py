import os
import shutil
import argparse
from sklearn.model_selection import train_test_split
import pandas as pd


def split_dataset(data_dir, output_dir, train_ratio=0.7, val_ratio=0.15, test_ratio=0.15, seed=42):
    """
    划分数据集并保持类别平衡
    参数:
        data_dir (str): 原始数据集路径（按类别分文件夹存放）
        output_dir (str): 划分后的输出路径
        train_ratio (float): 训练集比例
        val_ratio (float): 验证集比例
        test_ratio (float): 测试集比例
        seed (int): 随机种子（确保可复现）
    """
    # 检查比例总和是否为1
    assert abs(train_ratio + val_ratio + test_ratio - 1.0) < 1e-6, "比例总和必须为1"
    # 创建输出目录
    os.makedirs(output_dir, exist_ok=True)
    for subset in ['train', 'val', 'test']:
        os.makedirs(os.path.join(output_dir, subset), exist_ok=True)
    for subset in ['train', 'val', 'test']:
        os.makedirs(os.path.join(output_dir, subset), exist_ok=True)
    # 获取所有类别
    classes = [d for d in os.listdir(data_dir) if os.path.isdir(os.path.join(data_dir, d))]
    # 遍历每个类别进行划分
    for cls in classes:
        cls_dir = os.path.join(data_dir, cls)
        files = [f for f in os.listdir(cls_dir) if os.path.isfile(os.path.join(cls_dir, f))]
        # 第一次划分：分出训练集和临时集
        train_files, temp_files = train_test_split(
            files,
            train_size=train_ratio,
            random_state=seed,
            stratify=None  # 如果类别内需要分层可设置为 [cls]*len(files)
        )
        # 第二次划分：从临时集分出验证集和测试集
        val_test_ratio = val_ratio / (val_ratio + test_ratio)
        val_files, test_files = train_test_split(
            temp_files,
            train_size=val_test_ratio,
            random_state=seed
        )
        # 复制文件到目标目录
        for subset, subset_files in zip(['train', 'val', 'test'], [train_files, val_files, test_files]):
            subset_cls_dir = os.path.join(output_dir, subset, cls)
            os.makedirs(subset_cls_dir, exist_ok=True)
            for f in subset_files:
                src = os.path.join(cls_dir, f)
                dst = os.path.join(subset_cls_dir, f)
                shutil.copy(src, dst)
        print(f"类别 {cls} 划分完成: 训练集 {len(train_files)}, 验证集 {len(val_files)}, 测试集 {len(test_files)}")
    print("\n数据集划分完成，输出目录结构:")
    print(f"""
    {output_dir}
    ├── train
    │   ├── class1
    │   └── class2
    ├── val
    │   ├── class1
    │   └── class2
    └── test
        ├── class1
        └── class2
    """)

if __name__ == "__main__":
    parser = argparse.ArgumentParser(description="数据集划分工具")
    parser.add_argument("--data_dir", type=str, required=True, help="原始数据集路径")
    parser.add_argument("--output_dir", type=str, default="./split_data", help="输出路径")
    parser.add_argument("--train_ratio", type=float, default=0.7, help="训练集比例")
    parser.add_argument("--val_ratio", type=float, default=0.15, help="验证集比例")
    parser.add_argument("--test_ratio", type=float, default=0.15, help="测试集比例")
    parser.add_argument("--seed", type=int, default=42, help="随机种子")
    args = parser.parse_args()
    split_dataset(
        data_dir=args.data_dir,
        output_dir=args.output_dir,
        train_ratio=args.train_ratio,
        val_ratio=args.val_ratio,
        test_ratio=args.test_ratio,
        seed=args.seed
    )