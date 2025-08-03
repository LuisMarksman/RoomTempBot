// Google Apps Script: Telegram Bot Integration with Google Sheets
// Sanitized version for GitHub upload

function doPost(e) {
  var data = JSON.parse(e.postData.contents);
  var chatId = data.message.chat.id;
  var text = data.message.text;

  if (text === "/temp") {
    var sheet = SpreadsheetApp.openById("YOUR_SPREADSHEET_ID_HERE").getSheetByName("SensorData");
    var lastRow = sheet.getLastRow();
    var temp = sheet.getRange(lastRow, 2).getValue(); // Column B
    var humid = sheet.getRange(lastRow, 3).getValue(); // Column C

    var message = "Room temperature is " + temp + "°C and humidity is " + humid + "%.";
    sendTelegramMessage(chatId, message);
  }
}

function sendTelegramMessage(chatId, message) {
  var token = "YOUR_BOT_TOKEN_HERE"; // Replace with your Telegram bot token
  var url = "https://api.telegram.org/bot" + token + "/sendMessage";

  var payload = {
    "chat_id": chatId,
    "text": message
  };

  var options = {
    "method": "post",
    "contentType": "application/json",
    "payload": JSON.stringify(payload)
  };

  UrlFetchApp.fetch(url, options);
}

function doGet(e) {
  return ContentService.createTextOutput("Bot is online.");
}
