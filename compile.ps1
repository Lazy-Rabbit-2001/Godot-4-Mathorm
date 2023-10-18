$PSScriptRoot
Write-Host "About to start compiling." -ForegroundColor yellow
Start-Sleep -Seconds 3
Write-Host "Compiling for Windows" -ForegroundColor green
scons platform=windows
scons platform=windows target=template_release
Write-Host "Compiling for Linux" -ForegroundColor cyan
scons platform=linux
scons platform=linux target=template_release
Write-Host "Compiling for MacOS" -ForegroundColor orange
scons platform=macos
scons platform=macos target=template_release
Write-Host "Compiling for Android" -ForegroundColor lime
scons platform=android
scons platform=android target=template_release
Write-Host "Compiling for iOS" -ForegroundColor pink
scons platform=ios
scons platform=ios target=template_release
Write-Host "Compiling for JavaScript" -ForegroundColor blue
scons platform=javascript
scons platform=javascript target=template_release
Write-Host "Compiling finished, closing runner." -ForegroundColor yellow
Start-Sleep -Seconds 2