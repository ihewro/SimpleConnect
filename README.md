# c++ 简单socket例子

socket是什么？

计算机与计算之间传输数据的一种方法，由ip、端口号和传输协议构成。

我们的例子里面ip使用ipv4，tcp作为协议模拟。

* server处理和分发信息
* client发送和接收信息

client发送消息：

1. @用户名 只给某个人转发发消息
2. 直接发送的话 会给所有当前连接的用户发送消息