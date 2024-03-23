# 数据存储模块

## 基本思路

数据存储模块的基本思路为：

UI互动 -> 缓存到内存中 -> 在合适的时机保存到数据库中。

其中database部分为数据库模块，memoryCache部分为缓存模块。

## database模块

数据库表格式如下：

### GlobalConfig（全局配置）

### Stage（关卡）

| 列名           | 数据类型 | 备注     |
| -------------- | -------- | -------- |
| stage_id(主键) | int      | 关卡id   |
| stage_name     | varchar  | 关卡名称 |

### StageEvent（关卡事件）

| 列名           | 数据类型 | 备注                                        |
| -------------- | -------- | ------------------------------------------- |
| event_id(主键) | int      | 事件id                                      |
| event_time     | int      | 触发时间(TODO... 确认时间含义，是不是帧)    |
| event_type     | int      | 事件类型（枚举）                            |
| data           | varchar  | json格式，格式为：{"aaa":3.14,"bbb":15.926} |
| data_str       | varchar  | json格式，格式为：{"aaa":"test,"bbb":"abc"} |

### Role（自机）

| 列名          | 数据类型 | 备注                                 |
| ------------- | -------- | ------------------------------------ |
| role_id(主键) | int      | 自机id                               |
| role_name     | varchar  | 自机名称                             |
| picture_id    | varchar  | 自机图像（TODO... 构思后续存储方式） |

### Enemy（敌机）

| 列名           | 数据类型 | 备注                                        |
| -------------- | -------- | ------------------------------------------- |
| enemy_id(主键) | int      | 敌机id                                      |
| enemy_name     | varchar  | 敌机名称（可为空）                          |
| data           | varchar  | json格式，格式为：{"aaa":3.14,"bbb":15.926} |
| data_str       | varchar  | json格式，格式为：{"aaa":"test,"bbb":"abc"} |
| picture_id     | varchar  | 敌机图像（TODO... 构思后续存储方式）        |

### Bullet（子弹）

| 列名            | 数据类型 | 备注                                        |
| --------------- | -------- | ------------------------------------------- |
| bullet_id(主键) | int      | 子弹id                                      |
| bullet_name     | varchar  | 子弹名称（可为空）                          |
| data            | varchar  | json格式，格式为：{"aaa":3.14,"bbb":15.926} |
| data_str        | varchar  | json格式，格式为：{"aaa":"test,"bbb":"abc"} |
| picture_id      | varchar  | 敌机图像（TODO... 构思后续存储方式）        |

### audio（音频）

| 列名           | 数据类型 | 备注                                 |
| -------------- | -------- | ------------------------------------ |
| audio_id(主键) | int      | 音频id                               |
| audio_name     | varchar  | 音频名称（可为空）                   |
| audio_data     | blob     | 音频内容（TODO... 构思后续存储方式） |

### image（图像）

| 列名           | 数据类型 | 备注               |
| -------------- | -------- | ------------------ |
| image_id(主键) | int      | 图像id             |
| image_name     | varchar  | 图像名称（可为空） |
| image_data     | blob     | 图像内容           |

### Dialog（对话）

| 列名            | 数据类型 | 备注                                      |
| --------------- | -------- | ----------------------------------------- |
| dialog_id(主键) | int      | 对话id                                    |
| dialog_data     | varchar  | 对话内容，json格式，格式为：["aaa","bbb"] |
