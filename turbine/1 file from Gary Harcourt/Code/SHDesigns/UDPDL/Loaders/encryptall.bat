mkdir ..\encrypted-p
for %%x in (*.bin) do ..\encryptbin %%x ..\encrypted-p\%%x 
