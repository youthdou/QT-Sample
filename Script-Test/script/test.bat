@echo off
rem echo 'Copy lib,entity,model in the bin folder...'
echo %1
echo %2
if %2 == Base goto base-version
if %2 == Reader goto reader-version

:base-version
echo "Base Version"
::if not exist %~f1\README.md echo "Not Exsit README.md"
if not exist %~f1\README.md  copy %~f1\..\README.md %~f1\ /y
::copy %~f1\..\README.md %~f1\ /y
::if not exist README.md copy ..\README.md .\ /y
goto end

:end
echo "Finish"


::cd %~dp0
::echo %1
::rmdir /s/q %1\lib
::xcopy ..\..\VAT\lib-VS %1\lib\ /y /s /e
::if not exist %1\entity xcopy ..\..\VAT\entity %1\entity\ /y /s /e
::if not exist %1\model xcopy ..\..\VAT\model %1\model\ /y /s /e
::if not exist %1\Floats xcopy ..\..\VAT\Floats %1\Floats\ /y /s /e
::if not exist %1\3D xcopy ..\..\VAT\3D %1\3D\ /y /s /e
::if not exist %1\WelcomeChartImage xcopy ..\..\VAT\WelcomeChartImage %1\WelcomeChartImage\ /y /s /e
::if not exist %1\hyjj.chm copy ..\..\VAT\hyjj.chm %1\ /y
:: if not exist splash1.gif copy ..\..\..\VAT\splash1.gif .\ /y
:: if not exist splash2.gif copy ..\..\..\VAT\splash2.gif .\ /y
:: if not exist splash3.gif copy ..\..\..\VAT\splash3.gif .\ /y
:: if not exist splash4.gif copy ..\..\..\VAT\splash4.gif .\ /y
::if not exist %1\splash.gif copy ..\..\VAT\splash.gif %1\ /y
::if not exist %1\temp copy ..\..\VAT\temp %1\ /y
::if not exist %1\Data xcopy ..\..\VAT\Data %1\Data\ /y /s /e
::copy ..\Plugins\Submodules\*.dll %1\ /y
::copy ..\Plugins\Submodules\*.lib %1\lib /y
::copy ..\..\VAT\binX86-VS\*.dll %1\ /y