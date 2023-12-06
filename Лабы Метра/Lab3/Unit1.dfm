object Form1: TForm1
  Left = 0
  Top = 0
  Caption = 'Form1'
  ClientHeight = 715
  ClientWidth = 1282
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -18
  Font.Name = 'Tahoma'
  Font.Style = []
  OldCreateOrder = False
  PixelsPerInch = 96
  TextHeight = 22
  object Label1: TLabel
    Left = 40
    Top = 108
    Width = 143
    Height = 22
    Caption = #1058#1077#1082#1089#1090' '#1087#1088#1086#1075#1088#1072#1084#1084#1099
  end
  object LError: TLabel
    Left = 40
    Top = 616
    Width = 161
    Height = 22
    Caption = #1055#1088#1086#1080#1079#1086#1096#1083#1072' '#1086#1096#1080#1073#1082#1072
    Color = clRed
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clRed
    Font.Height = -18
    Font.Name = 'Tahoma'
    Font.Style = []
    ParentColor = False
    ParentFont = False
    Visible = False
  end
  object Label2: TLabel
    Left = 465
    Top = 107
    Width = 52
    Height = 22
    Caption = #1057#1087#1077#1085#1099
  end
  object Label3: TLabel
    Left = 1025
    Top = 91
    Width = 140
    Height = 22
    Caption = #1052#1077#1090#1088#1080#1082#1072' '#1063#1077#1087#1080#1085#1072' '
  end
  object Label4: TLabel
    Left = 1025
    Top = 107
    Width = 113
    Height = 22
    Caption = #1074#1074#1086#1076#1072'/'#1074#1099#1074#1086#1076#1072
  end
  object Label5: TLabel
    Left = 744
    Top = 107
    Width = 205
    Height = 22
    Caption = #1055#1086#1083#1085#1072#1103' '#1084#1077#1090#1088#1080#1082#1072' '#1063#1077#1087#1080#1085#1072' '
  end
  object Memo1: TMemo
    Left = 40
    Top = 136
    Width = 401
    Height = 449
    ScrollBars = ssBoth
    TabOrder = 0
  end
  object BLoad: TButton
    Left = 40
    Top = 16
    Width = 161
    Height = 58
    Caption = #1047#1072#1075#1088#1091#1079#1080#1090#1100
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -16
    Font.Name = 'Tahoma'
    Font.Style = []
    ParentFont = False
    TabOrder = 1
    OnClick = BLoadClick
  end
  object Button1: TButton
    Left = 848
    Top = 8
    Width = 193
    Height = 66
    Caption = #1057#1086#1093#1088#1072#1085#1080#1090#1100
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -16
    Font.Name = 'Tahoma'
    Font.Style = []
    ParentFont = False
    TabOrder = 2
    OnClick = Button1Click
  end
  object Button2: TButton
    Left = 465
    Top = 8
    Width = 193
    Height = 65
    Caption = #1055#1086#1076#1089#1095#1080#1090#1072#1090#1100
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -16
    Font.Name = 'Tahoma'
    Font.Style = []
    ParentFont = False
    TabOrder = 3
    OnClick = Button2Click
  end
  object Memo2: TMemo
    Left = 465
    Top = 135
    Width = 249
    Height = 450
    ScrollBars = ssBoth
    TabOrder = 4
  end
  object Memo3: TMemo
    Left = 744
    Top = 135
    Width = 249
    Height = 450
    ScrollBars = ssBoth
    TabOrder = 5
  end
  object Memo4: TMemo
    Left = 1025
    Top = 135
    Width = 249
    Height = 450
    ScrollBars = ssBoth
    TabOrder = 6
  end
  object OpenDialog1: TOpenDialog
    Left = 232
    Top = 16
  end
  object SaveDialog1: TSaveDialog
    DefaultExt = '*.txt'
    Left = 320
    Top = 16
  end
end
