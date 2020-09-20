@echo off

cd Executions

echo ---------------------------------
echo 1. Test pdadd(Add New)
echo date:2020-04-26
echo text:What a nice day. Let's have a break and go outdoors!
echo ---------------------------------
@pdadd.exe 2020-04-26 "What a nice day." "Let's have a break and go outdoors!" .
echo.

echo ---------------------------------
echo 2. Test pdadd(Replace old)
echo date:2020-01-01
echo text:Achieve more in the new year~ Work Hard !!
echo ---------------------------------
@pdadd.exe 2020-01-01 "Achieve more in the new year~" "Work Hard !!" .
echo.

echo ---------------------------------
echo 3. Test pdlist(Without Limits)
echo date:all
echo ---------------------------------
@pdlist.exe
echo.

echo ---------------------------------
echo 4. Test pdlist(With Limits)
echo date:2020-01-01 ~ 2020-04-26
echo ---------------------------------
@pdlist.exe 2020-01-01 2020-04-26
echo.

echo ---------------------------------
echo 5. Test pdlist(0 match)
echo date:2020-05-01 ~ 2020-05-05
echo ---------------------------------
@pdlist.exe 2020-05-01 2020-05-05
echo.

echo ---------------------------------
echo 6. Test pdshow(Exist)
echo date:2020-01-01
echo ---------------------------------
@pdshow.exe 2020-01-01
echo.

echo ---------------------------------
echo 7. Test pdshow(Nonexist)
echo date:2020-01-02
echo ---------------------------------
@pdshow.exe 2020-01-02
echo.

echo ---------------------------------
echo 8. Test pdremove(Exist)
echo date:2020-04-24
echo ---------------------------------
@pdremove.exe 2020-04-24
echo.

echo ---------------------------------
echo 9. Test pdremove(Nonexist)
echo date:2020-01-02
echo ---------------------------------
@pdremove.exe 2020-01-02
echo.

pause