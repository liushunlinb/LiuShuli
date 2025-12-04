import torch
import torch.onnx
import torch.nn as nn

model = torch.load('fruits1_8.pth',map_location='cpu')
model.eval()

dummy_input = torch.randn(1, 3, 224, 224)

# 4. 使用torch.onnx.export将模型导出为ONNX格式
# 输入：模型，输入张量，ONNX文件路径，export_params=True表示将训练好的参数一同导出
torch.onnx.export(model,
                  dummy_input,
                  "fruits1_8.onnx",
                  export_params=True,
                  opset_version=12,
                  input_names=['input'],
                  output_names=['output'],
                  dynamic_axes={'input': {0: 'batch_size'}, 'output': {0: 'batch_size'}} # 动态轴信息
                 )

print("模型已成功导出为ONNX格式。")