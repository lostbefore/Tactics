# Tactics
2250944 谌乐俊杰 大作业日记<br/>
深夜更改商店 </font>  
===
今天晚上，队友跟我反馈：先选第五个”商品“，就无法购买第一个"商品"。  
我也调试了一下，还真的是这样，debug了一会儿，发现displayPlayer()里 judgeCanBought[4] = 0;写成judgeCanBought[0] = 0;
难怪点不了第一个“商品”！
其次，我在warmap.cpp上增加了每一回合，商店资源金币的刷新、补充功能。
效果特别好！
