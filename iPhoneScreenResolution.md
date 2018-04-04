# Introduction
You've jailbroken your iPad, iPhone, what have you. Congratulations! Now you can tinker with things you couldn't tinker with in the "jailed" OS. But with this greater amount of freedom comes with more opportunities to mess up your device, sometimes to the point of completely bricking it! 

# Problem
In this case, you've set a custom screen resolution on your iDevice and it's too out of range for the screen to display anything and it just displays black.
If you have a semi-tethered jailbreak (like Electra for iOS 11.0-11.1.2), you may think that because it's a semi-tethered jailbreak, you can just restart and it will boot without any of your tweaks or customizations. No big deal.
Well, it seems that changing your resolution still stays even when it's in its "jailed" state, meaning that the screen still won't display correctly even after a restart.

# Solution 1

### Things Needed
   - Lightning cable (or 30-pin cable if your iDevice is *that* old)
   - Computer
   - [3uTools](http://www.3u.com/)

#### If you have no passcode/have a passcode but did not restart after changing resolution
That makes this process significantly easier. You would need to do the following:
1. Enable voiceover via asking Siri
   - Remember that with voiceover on, you can tap on something once to get that thing read to you, and tap twice on a button to actually perform the action. 
2. Install [3uTools](http://www.3u.com/)
3. Connect iDevice to computer and trust the computer if it isn't already (using voiceover to find which button you're on)
4. Click on Toolbox > Realtime screen
   - Now you'll be able to see your screen on your computer
5. Change the screen resolution to a known safe screen resolution, found [here](https://developer.apple.com/library/content/documentation/DeviceInformation/Reference/iOSDeviceCompatibility/Displays/Displays.html)
6. Your iDevice should now be showing picture, and you're all done!
   - Note that afterwards, you may need to set your resolution higher as iOS seems to run at a higher resolution than found on Apple's website. For instance, the iPhone 7+ seems to run at 2208x1242, even though the Apple website states it's 1920x1080.

#### If you have a passcode and restarted after changing resolution
The process gets harder as you will need to type your passcode basically blindly for the first time (as TouchID/FaceID is disabled for the first time after a restart). I recommend disabling vibrate so that you can at least hear that you're tapping on a number/letter.
I also recommend looking at a picture of the [passcode lockscreen](https://media.idownloadblog.com/wp-content/uploads/2017/06/Creamy-iOS-10-Lighter-Cream.jpg) or [password lockscreen](https://img.gadgethacks.com/img/88/42/63559176523076/0/set-alphanumeric-lock-screen-passcode-for-stronger-security-your-iphone.w1456.jpg). This may take more than one try. \n

(Also, I'm not sure if the touch input still stays the same; I personally set my screen resolution too high and mixed the height and width values, but the number placement on my iPhone 7+ was still seemingly the same.)
   
You are able to verify you've gotten to the home screen by pressing the lock button and listening for the locking sound.

Another thing that's different is that if the computer isn't trusted, you will not only need to tap "Trust This Computer", but you will also have to enter your passcode as an extra security measure. This one shouldn't be as difficult if you've enabled voiceover.
After that, you should just be able to follow the instructions above to restore your screen resolution.

# Solution 2
**NOTE: This solution will cause all data to be lost!**

### Things Needed
   - Computer

So, you're not able to get your passcode, but you don't want to update your device since that update may be unjailbreakable? Well, there seems to be an answer to that; however, it resets your device completely.
If you have "Find My iPhone" enabled (which seems to be enabled by default after signing in with your Apple account), you should be able to remotely reset your device, which is the equivalent of the "Erase All Contents and Settings" button on the Settings app. This process should keep your iOS version the same.

You would need to do the following:
1. Go to [Find My iPhone on iCloud](https://www.icloud.com/#find)
2. Select the iDevice in question from your list of iDevices
3. Wait for your iDevice to be located
4. Click on "Erase"
5. Confirm the action on the popup box
6. Your iDevice, upon receiving this request, will now being the reset process
7. After this process, you screen should now display correctly, and you'll now have to re-install everything and re-jailbreak (if applicable).

# "Solution" 3
**NOTE: This solution will also cause all data to be lost, and should only be considered if neither solution works for you.**

### Things Needed
   - Lightning cable (or 30-pin cable if your iDevice is *that* old)
   - Computer

So, you've come to a point where you're, for whatever reason:
   - Not able to get into your iDevice at all
   - Not able to remotely erase your iDevice via iCloud

There's only one thing now, and that's an iTunes restore. This will update your iOS version, so you may not be able to jailbreak your iDevice anymore after this process. 
   - Unless you have blobs saved, then you *might* be able to install an unsigned iOS version

But after this, everything should be restored to default settings and your screen should now be able to display picture once again.
