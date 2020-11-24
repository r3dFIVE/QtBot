function Component() { }

Component.prototype.createOperations = function()
{
    component.createOperations();

    if (systemInfo.productType === "windows") {
        component.addOperation("CreateShortcut", "@TargetDir@/bot.exe", "@StartMenuDir@/QtBot.lnk",
            "workingDirectory=@TargetDir@", "iconPath=%SystemRoot%/system32/SHELL32.dll",
            "iconId=1", "description=Start QtBot!");

        component.addOperation("CreateShortcut", "@TargetDir@/maintenancetool.exe", "@StartMenuDir@/README.lnk",
            "workingDirectory=@TargetDir@", "iconPath=%SystemRoot%/system32/SHELL32.dll",
            "iconId=2", "description=Remove installed QtBot components.");

        component.addOperation("CreateShortcut", "@TargetDir@/readme.txt", "@StartMenuDir@/README.lnk",
            "workingDirectory=@TargetDir@", "iconPath=%SystemRoot%/system32/SHELL32.dll",
            "iconId=3", "description=Open README file");

        component.addOperation("CreateShortcut", "@TargetDir@/license.txt", "@StartMenuDir@/GPLv3 License.lnk",
            "workingDirectory=@TargetDir@", "iconPath=%SystemRoot%/system32/SHELL32.dll",
            "iconId=3", "description=Open GPLv3 License.");
    }
}
