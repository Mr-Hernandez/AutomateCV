@echo off
:: This will zip a folder

echo "Zipping file..."
powershell -Command "Compress-Archive -Path moddedFile/* -DestinationPath moddedFile"
powershell -Command "Remove-Item moddedFile -Recurse"
