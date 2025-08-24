#!/bin/bash

# Define the target pattern
TARGET_PATTERN="*5.10.223*"

# Find and remove files and directories matching the pattern in the /boot directory
sudo find /boot -name "$TARGET_PATTERN" -exec rm -rf {} +

echo "All files and folders in /boot containing '5.10.223' have been removed."

sudo update-grub
