# Aciona Sistema de Iluminação TCC
Código aplicado no ESP32 para acionamento do sistema de suplementação luminosa.
A ferramenta conecta ao banco de dados e muda seu Status.

O código consulta o tempo o tempo que o sistema de iluminação deve ficar ligado e então manda o sital para o RELÉ.



#### Script da planilha [STATUS](https://docs.google.com/spreadsheets/d/1RCYBbdXH1hzrEg2qwlLmCxcVZYAFwF5VYIUPBIEIHHk/edit?gid=589520110#gid=589520110)  que é executado para mudar o Status
```js
function doGet(e) {
var sheet = SpreadsheetApp.openById("1RCYBbdXH1hzrEg2qwlLmCxcVZYAFwF5VYIUPBIEIHHk").getSheetByName("STATUS");
var ultima_linha = sheet.getLastRow();
var estado = sheet.getRange("C"+ultima_linha).getValue();
return ContentService.createTextOutput(estado);
    }
```

#### Script da planilha [DLI TOTAL](https://docs.google.com/spreadsheets/d/1RCYBbdXH1hzrEg2qwlLmCxcVZYAFwF5VYIUPBIEIHHk/edit?gid=300404180#gid=300404180) que busca o tempo de suplementação
```js
function doGet(e) {
  var sheet = SpreadsheetApp.openById("1RCYBbdXH1hzrEg2qwlLmCxcVZYAFwF5VYIUPBIEIHHk").getSheetByName("DLI_TOTAL");
  var colunaA = sheet.getRange("A:A").getValues();
  var ultima_linha = colunaA.filter(String).length;
  var tempo = sheet.getRange("D"+ultima_linha).getValue();
  return ContentService.createTextOutput(tempo);
}
```
