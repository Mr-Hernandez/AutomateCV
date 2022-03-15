@echo off
::This part will unzip file

echo "Unzipping file..."
powershell -Command "Expand-Archive moddedFile.zip -DestinationPath moddedFile"
echo