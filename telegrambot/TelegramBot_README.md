Telegram Bot Setup Guide for Room Temperature Tracker
This guide helps you set up a Telegram bot to retrieve temperature and humidity data from Google Sheets.

Step-by-Step Instructions

1. Create a Telegram Bot
Open Telegram and search for @BotFather
Start a chat and type /newbot
Give your bot a name (e.g., RoomTempBot)
Choose a unique username ending with bot (e.g., room_temp_tracker_bot)
You will receive a Bot Token (e.g., 123456789:ABCdefGHIjklMNOpqrSTUvwxYZ)
 Save the bot token securely. You'll need it in the Google Apps Script.

2. Connect Your Bot to Google Apps Script
Open your Apps Script project (Code.gs)
Replace:
"YOUR_BOT_TOKEN_HERE" with your actual token
"YOUR_SPREADSHEET_ID_HERE" with your Google Sheet ID
Deploy your script as a Web App:
Click Deploy > Manage deployments
Click New Deployment
Set:
Description: Telegram Webhook
Execute as: Me
Access: Anyone
Click Deploy
Copy the Web App URL
3. Set the Bot Webhook
In your browser, visit:

https://api.telegram.org/bot<YOUR_BOT_TOKEN>/setWebhook?url=<YOUR_WEB_APP_URL>

Example:

https://api.telegram.org/bot123456789:ABCdefGHI/setWebhook?url=https://script.google.com/macros/s/AKfycbxyz123456/exec

If successful, you'll get:

{"ok":true,"result":true,"description":"Webhook was set"}

4. Use the Bot
Open your bot in Telegram (from the username you created)
Send /temp
The bot will reply with the latest temperature and humidity from your sheet
 Requirements
Google Sheet named "SensorData" with:

Column A: Timestamp
Column B: Temperature
Column C: Humidity
Google Apps Script set up and deployed as Web App

 Example Conversation
User: /temp
Bot: Room temperature is 28.5°C and humidity is 67%.
