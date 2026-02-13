use prod for windows commiting and pushing to main dangerously
usage prod <commit message>

prod definition:

#!/bin/bash
   
   if [ -z "$1" ]; then
       echo "Error: Commit message required"
       echo "Usage: prod <commit message>"
       exit 1
   fi
   
   git add .
   git commit -m "$1"
   git push -u origin main

#powershell
function prod {
    param([string]$message)
    
    if ([string]::IsNullOrWhiteSpace($message)) {
        Write-Host "Error: Commit message required"
        Write-Host "Usage: prod <commit message>"
        return
    }
    
    git add .
    git commit -m $message
    git push -u origin main
}