# M5STACK IC AW32001 Driver

本组件主要为M5STACK搭载AW32001电源管理芯片的硬件提供驱动支持


| 墨水屏型号 | 支持程度 | 支持mcu | 框架支持 | 备注     |
| ---------- | -------- | ------- | -------- | -------- |
| AW32001    | √       | esp32   | ESP-IDF  | 尚不完善 |
|            | ×       |         |          |          |

## 添加到项目

1. 通过乐鑫的组件服务添加软件包（暂不支持）

```powershell
 idf.py add-dependency m5_ic_aw32001 == 1.0.4
```

1. 通过M5STACK内部代码仓库添加软件包

```yaml
  m5_ic_aw32001:
    version: '*'
    git: https://{account}:{password}@gitlab.m5stack.com/embedded-common-components/m5_aw32001.git

```
