# ComputerApplication_test
## **病毒模擬器**

一國家共有**2000**位國民及**30x30**平方單位之國土，  

自第一位國民感染，共經過**300**天，  

每一天同一單位上的國民兩兩接觸，  

輸出結果為300天後國民健康調查。  

----
   
傳播機率｜**STRONG**  

病毒強度｜**AxB^(感染天數)**   

以上參數以**mutatione=0.01**每天進行一次病變且移動一單位  

病毒強度超過**LETHAL=100**則為死亡  

---
函數                                 | 參數      |     回傳類型 | 執行             | 呼叫
---- | ---- | ---- | ---- | ----
cCountry::cCountry()                | _            | 建構函數 | 設定第一人感染     | f()  
cCountry::f()                       | _            | Void    | 處理向量及決定座標 | _  
cCountry::RandomInfect()            | _            | Void    | 抓人感染         | InfectAnother(cHuman*, int), makep(double, double, double)  
cHuman::InfectAnother(cHuman*, int) | 第二人, 第幾天 | bool    | 以隨機決定是否感染 | _  
cCountry::Tomorrow()                | _            | Void    | 時間和參數變異推進 | muta(), Died(int)  
cHuman::Died(int)                   | 第幾天        | bool    | 決定是否死亡      | VirusLevel(int)  
cHuman::VirusLevel(int)             | 第幾天        | double  | 回傳病毒數值      | _  


