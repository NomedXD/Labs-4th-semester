unit fMain;

interface

uses
  Winapi.Windows, Winapi.Messages, System.SysUtils, System.Variants,
  System.Classes, Vcl.Graphics,
  Vcl.Controls, Vcl.Forms, Vcl.Dialogs, Vcl.StdCtrls;

type
  TfmMain = class(TForm)
    odOpenFile: TOpenDialog;
    sdSaveFile: TSaveDialog;
    memInput: TMemo;
    memOutput: TMemo;
    btOpen: TButton;
    btSave: TButton;
    cb�ipher: TComboBox;
    editKeyWord: TEdit;
    btEncrypt: TButton;
    btDecrypt: TButton;
    lbDecryptionStatus: TLabel;
    lbEncryptionStatus: TLabel;
    lbCipherStatus: TLabel;
    procedure btOpenClick(Sender: TObject);
    procedure btSaveClick(Sender: TObject);
    procedure btEncryptClick(Sender: TObject);
    procedure btDecryptClick(Sender: TObject);
    procedure cb�ipherChange(Sender: TObject);

  private
    { Private declarations }
  public
    { Public declarations }
  end;

type
  tArr = array [1 .. 4, 1 .. 4] of integer;

var
  fmMain: TfmMain;
  arr: tArr = ((0, 1, 1, 1), (1, 1, 1, 0), (1, 1, 0, 1), (1, 0, 1, 1));
  strArr: array [1 .. 500] of AnsiString;
  charArray: array [1 .. 4, 1 .. 4] of Char;

implementation

{$R *.dfm}
// �������� �� ������� ����� � ������
function isRussian(const letter: integer): boolean;
begin
  if ((letter >= ord(widechar('�'))) and (letter <= ord(widechar('�'))))
    or ((letter >= ord(widechar('�'))) and (letter <= ord(widechar('�'))
    )) or (letter = ord(widechar('�'))) or (letter = ord(widechar('�')))
  then
    Result := true
  else
    Result := false;
end;

// �������� �� ���������� ����� � ������
function isEnglish(const letter: integer): boolean;
begin
  if ((letter >= ord(widechar('A'))) and (letter <= ord(widechar('Z')))
    or ((letter >= ord(widechar('a'))) and
    (letter <= ord(widechar('z'))))) then
    Result := true
  else
    Result := false;

end;

// ������� ������� �� 90 ��������
procedure rotateArr(var arrP: tArr);
var
  i, x, p, k, j: integer;
begin
  p := 4 div 2; { ��������\�� ������� �� 4 ����� }
  for i := 1 to p do
    for k := i to 4 -
      i do { ������ �������� �� ����� �� ����� �������� � ������ }
    begin
      x := arrP[i, k];
      arrP[i, k] := arrP[4 - k + 1, i];
      arrP[4 - k + 1, i] := arrP[4 - i + 1, 4 - k + 1];
      arrP[4 - i + 1, 4 - k + 1] := arrP[k, 4 - i + 1];
      arrP[k, 4 - i + 1] := x;
    end;

end;

// ��������� ������ � ���������� ����
function getMemo1Text(const memInput: TMemo): String;
var
  i, j, letterCode: integer;
begin

  if fmMain.cb�ipher.ItemIndex = 1 then
    for i := 0 to memInput.Lines.Count - 1 do
      for j := 1 to Length(memInput.Lines[i]) do
      begin
        letterCode := ord(memInput.Lines[i][j]);
        if isRussian(letterCode) then
          Result := Result + AnsiUpperCase(chr(letterCode));
      end
  else if fmMain.cb�ipher.ItemIndex = 0 then
    for i := 0 to memInput.Lines.Count - 1 do
      for j := 1 to Length(memInput.Lines[i]) do
      begin
        letterCode := ord(memInput.Lines[i][j]);
        if isEnglish(letterCode) then
          Result := Result + AnsiUpperCase(chr(letterCode));
      end;
  // fmMain.memInput.Clear;
  // fmMain.memInput.Lines[0]:=Result;

end;

// ��������� ������ �����
function getKeyText(const keyInput: TEdit): String;
var
  buf, s: String;
  i: integer;
begin
  s := AnsiUpperCase(keyInput.Text);
  i := 1;
  if fmMain.cb�ipher.ItemIndex = 1 then
    while i <= Length(s) do
      if not(isRussian(ord(s[i]))) then
        delete(s, i, 1)
      else
        inc(i)
  else if fmMain.cb�ipher.ItemIndex = 0 then
    while i <= Length(s) do
      if not(isRussian(ord(s[i]))) then
        delete(s, i, 1)
      else
        inc(i);

  Result := s;
end;

// ������� �� ������ �������
procedure TfmMain.btOpenClick(Sender: TObject);
var
  str: String;
begin
  if odOpenFile.Execute then
    memInput.Lines.LoadFromFile(odOpenFile.FileName, TEncoding.UTF8);
end;

// ������� �� ������ ���������
procedure TfmMain.btSaveClick(Sender: TObject);
begin
  if sdSaveFile.Execute then
    if Pos('.txt', sdSaveFile.FileName) > 0 then
      memOutput.Lines.SaveToFile(sdSaveFile.FileName, TEncoding.UTF8)
    else
      memOutput.Lines.SaveToFile(sdSaveFile.FileName + '.txt', TEncoding.UTF8);
end;

// ���������� ����� � ����������� �� ����������
procedure TfmMain.cb�ipherChange(Sender: TObject);
begin
  if fmMain.cb�ipher.ItemIndex = 0 then
    editKeyWord.Enabled:=false
  else
    editKeyWord.Enabled:=true;

end;


function index(rusLetter: widechar): integer;
begin
  if (rusLetter >= '�') and (rusLetter <= '�') then
    Result := ord(rusLetter) - ord(widechar('�'))
  else if (rusLetter >= '�') then
    Result := ord(rusLetter) - ord(widechar('�')) + 1
  else
    Result := 6;
end;

function letterOf(index: integer): widechar;
begin
  if (index <= 5) then
    Result := widechar(chr(ord(widechar('�')) + index))
  else if (index >= 7) then
    Result := widechar(chr(ord(widechar('�')) + index - 1))
  else
    Result := widechar('�');
end;

procedure showError(lbError: TLabel; Text: String);
begin
  lbError.Caption := Text;
  lbError.Visible := true;
end;

procedure showSucces(lbSucces: TLabel; Text: String);
begin
  lbSucces.Caption := Text;
  lbSucces.Visible := true;
end;

function VishenerCipher(MorS, key: String; encrypt: boolean): String;
var
  i: integer;
begin
  Result := '';
  if encrypt then
    for i := 1 to Length(MorS) do
      Result := Result + letterOf((index(MorS[i]) + index(key[i])) mod 33)
  else
    for i := 1 to Length(MorS) do
    begin
      Result := Result +
        letterOf((index(MorS[i]) - index(key[i]) + 33) mod 33);
    end;
end;

function Matrix(const MorS: String; const encrypt: boolean): String;
var
  letter: widechar;
  i, j, k: integer;
  s: String;
  z, ch: integer;
begin
  Result := '';

  if encrypt then
  begin
    s := MorS;
    k := 1;
    ch := 65;
    repeat
      for z := 1 to 4 do
      begin
        for i := 1 to 4 do
        begin
          for j := 1 to 4 do
          begin
            if arr[i, j] = 0 then
            begin
              if k < s.Length + 1 then
              begin

                charArray[i, j] := s[k];
                inc(k);
              end
              else
              begin
                charArray[i, j] := chr(ch);
                inc(ch);
                if ch = 91 then
                  ch := ch - 26;
              end;
            end;
          end;
        end;
        rotateArr(arr);
      end;

      for i := 1 to 4 do
        for j := 1 to 4 do
          Result := Concat(Result, charArray[i, j]);
    until k>s.Length;
  end
  else
  begin
    s := MorS;
    k := 1;
    repeat

      for i := 1 to 4 do
        for j := 1 to 4 do
        begin
          charArray[i, j] := s[k];
          inc(k);
        end;
      for z := 1 to 4 do
      begin
        for i := 1 to 4 do
          for j := 1 to 4 do
          begin
            if arr[i, j] = 0 then
            begin
              Result := Result + charArray[i, j];

            end;

          end;

        rotateArr(arr);
      end;
    until k > s.Length;

  end;
end;

// ����������
procedure TfmMain.btEncryptClick(Sender: TObject);
var
  str, key: String;
  keylen, z, i: integer;
begin
  lbCipherStatus.Visible := false;
  lbDecryptionStatus.Visible := false;
  lbEncryptionStatus.Visible := false;
  memOutput.Text := '';

  str := getMemo1Text(memInput);
  key := getKeyText(editKeyWord);

  if cb�ipher.ItemIndex = -1 then
    showError(lbCipherStatus, '�������� ����� ����������!');
  if ((key = '') or (str = '')) and (fmMain.cb�ipher.ItemIndex = 1) then
    showError(lbEncryptionStatus,
      '� ��������� ������ �/��� ����� ����������� ������� �������!')
  else if ((str = '') and (fmMain.cb�ipher.ItemIndex = 0)) then
    showError(lbEncryptionStatus,
      '� ��������� ������ ����������� ���������� �������!')
  else if cb�ipher.ItemIndex <> -1 then
  begin
    if cb�ipher.ItemIndex = 1 then
    begin
      keylen := key.Length;
      z := 1;
      while key.Length <> str.Length do
      begin
        for i := 1 to keylen do
        begin
          key := key + letterOf((index(key[i]) + z) mod 33);
          if key.Length = str.Length then
            break;

        end;
        inc(z);
      end;

      memOutput.Text := VishenerCipher(str, key, true);
    end
    else if cb�ipher.ItemIndex = 0 then
      memOutput.Text := Matrix(str, true);
    showSucces(lbEncryptionStatus, '���������!');
  end;
end;

// ����������
procedure TfmMain.btDecryptClick(Sender: TObject);
var
  str, key: String;
  keylen, z, i: integer;
begin
  lbCipherStatus.Visible := false;
  lbDecryptionStatus.Visible := false;
  lbEncryptionStatus.Visible := false;
  memOutput.Text := '';

  str := getMemo1Text(memInput);
  key := getKeyText(editKeyWord);

  if cb�ipher.ItemIndex = -1 then
    showError(lbCipherStatus, '�������� ����� ����������!');
  if ((key = '') or (str = '')) and (fmMain.cb�ipher.ItemIndex = 1) then
    showError(lbEncryptionStatus,
      '� ��������� ������ �/��� ����� ����������� ������� �������!')
  else if ((str = '') and (fmMain.cb�ipher.ItemIndex = 0)) then
    showError(lbEncryptionStatus,
      '� ��������� ������ ����������� ���������� �������!')
  else if cb�ipher.ItemIndex <> -1 then
  begin
    if cb�ipher.ItemIndex = 1 then
    begin
      keylen := key.Length;
      z := 1;
      while key.Length <> str.Length do
      begin
        for i := 1 to keylen do
        begin
          key := key + letterOf((index(key[i]) + z) mod 33);
          if key.Length = str.Length then
            break;

        end;
        inc(z);
      end;

      memOutput.Text := VishenerCipher(str, key, false);
    end
    else if cb�ipher.ItemIndex = 0 then
      memOutput.Text := Matrix(str, false);
    showSucces(lbDecryptionStatus, '���������!');
  end;
end;

end.
