object fmMain: TfmMain
  Left = 0
  Top = 0
  Caption = 'En/De-coder'
  ClientHeight = 653
  ClientWidth = 819
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  OldCreateOrder = False
  PixelsPerInch = 96
  TextHeight = 13
  object lbDecryptionStatus: TLabel
    Left = 32
    Top = 263
    Width = 132
    Height = 19
    Caption = 'lbDecryptionStatus'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -16
    Font.Name = 'Tahoma'
    Font.Style = []
    ParentFont = False
    Visible = False
  end
  object lbEncryptionStatus: TLabel
    Left = 32
    Top = 263
    Width = 118
    Height = 18
    Caption = 'lbEncryptionStatus'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -15
    Font.Name = 'Tahoma'
    Font.Style = []
    ParentFont = False
    Visible = False
  end
  object lbCipherStatus: TLabel
    Left = 160
    Top = 37
    Width = 91
    Height = 18
    Caption = 'lbCipherStatus'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -15
    Font.Name = 'Tahoma'
    Font.Style = []
    ParentFont = False
    Visible = False
  end
  object memInput: TMemo
    Left = 32
    Top = 56
    Width = 513
    Height = 201
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -19
    Font.Name = 'Tahoma'
    Font.Style = []
    ParentFont = False
    ScrollBars = ssHorizontal
    TabOrder = 0
  end
  object memOutput: TMemo
    Left = 32
    Top = 378
    Width = 513
    Height = 201
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -19
    Font.Name = 'Tahoma'
    Font.Style = []
    Lines.Strings = (
      '')
    ParentFont = False
    ScrollBars = ssHorizontal
    TabOrder = 1
  end
  object btOpen: TButton
    Left = 32
    Top = 8
    Width = 81
    Height = 34
    Caption = #1054#1090#1082#1088#1099#1090#1100
    TabOrder = 2
    OnClick = btOpenClick
  end
  object btSave: TButton
    Left = 32
    Top = 585
    Width = 81
    Height = 34
    Caption = #1057#1086#1093#1088#1072#1085#1080#1090#1100
    TabOrder = 3
    OnClick = btSaveClick
  end
  object cbСipher: TComboBox
    Left = 160
    Top = 8
    Width = 137
    Height = 21
    Hint = #1052#1077#1090#1086#1076' '#1096#1080#1092#1088#1086#1074#1072#1085#1080#1103
    Style = csDropDownList
    ParentShowHint = False
    ShowHint = False
    TabOrder = 4
    TextHint = #1052#1077#1090#1086#1076' '#1096#1080#1092#1088#1086#1074#1072#1085#1080#1103
    OnChange = cbСipherChange
    Items.Strings = (
      #1055#1086#1074#1086#1088#1086#1090' '#1084#1072#1090#1088#1080#1094#1099
      #1040#1083#1075#1086#1088#1080#1090#1084' '#1042#1080#1078#1077#1085#1077#1088#1072)
  end
  object editKeyWord: TEdit
    Left = 320
    Top = 8
    Width = 225
    Height = 21
    TabOrder = 5
    TextHint = #1050#1083#1102#1095#1077#1074#1086#1077' '#1089#1083#1086#1074#1086'...'
  end
  object btEncrypt: TButton
    Left = 656
    Top = 198
    Width = 121
    Height = 59
    Caption = #1047#1072#1096#1080#1092#1088#1086#1074#1072#1090#1100
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -15
    Font.Name = 'Tahoma'
    Font.Style = []
    ParentFont = False
    TabOrder = 6
    OnClick = btEncryptClick
  end
  object btDecrypt: TButton
    Left = 656
    Top = 378
    Width = 121
    Height = 59
    Caption = #1044#1077#1096#1080#1092#1088#1086#1074#1072#1090#1100
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -15
    Font.Name = 'Tahoma'
    Font.Style = []
    ParentFont = False
    TabOrder = 7
    OnClick = btDecryptClick
  end
  object odOpenFile: TOpenDialog
    DefaultExt = '*.txt'
    Filter = #1058#1077#1082#1089#1090#1086#1074#1099#1077' '#1092#1072#1081#1083#1099'|*.txt'
    Left = 624
    Top = 16
  end
  object sdSaveFile: TSaveDialog
    Filter = #1058#1077#1082#1089#1090#1086#1074#1099#1077' '#1092#1072#1081#1083#1099'|*.txt'
    Left = 696
    Top = 16
  end
end
