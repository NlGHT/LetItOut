function Component()
{
    // Default constructor
}

Component.prototype.createOperations = function()
{
    // Call default implementation to actually install executable!
    component.createOperations();

    if (systemInfo.productType === "windows") {
        component.addOperation("CreateShortcut", "@TargetDir@/LetItOut.exe", "@StartMenuDir@/Let It Out.lnk",
            "workingDirectory=@TargetDir@");
    }
}
