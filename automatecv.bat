@echo off
::This part will unzip file

echo "Unzipping file..."
powershell -Command "Expand-Archive aa.zip -DestinationPath crap"
echo