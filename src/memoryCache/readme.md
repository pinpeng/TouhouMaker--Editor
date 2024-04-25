# 数据缓存模块

负责内存与磁盘中的数据交互

将磁盘中保存的数据读到内存中，并展现到ui上面

或者将内存中的数据存储到磁盘中

## 模块结构

~~~shell
memoryCache
├─globalEntity			
├─interface
└─projectEntity
~~~

* globalEntity：编辑器数据（比如主题颜色等）
* interface：项目接口
* projectEntity：项目数据（比如项目中设定的子弹、人物等）

## 其他

本来是想要将内存数据以数据库的形式保存到磁盘中，结果发现game maker官方好像并不支持数据库解析，所以就先这样吧（