object Form1: TForm1
  Left = 78
  Top = 0
  Caption = 'Cells!'
  ClientHeight = 720
  ClientWidth = 1280
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  KeyPreview = True
  OldCreateOrder = False
  OnDestroy = FormDestroy
  OnKeyPress = FormKeyPress
  OnResize = FormResize
  PixelsPerInch = 96
  TextHeight = 13
  object PaintBox1: TPaintBox
    Left = 0
    Top = 0
    Width = 1008
    Height = 720
    OnMouseDown = PaintBox1MouseDown
    OnMouseMove = PaintBox1MouseMove
    OnMouseUp = PaintBox1MouseUp
    OnPaint = PaintBox1Paint
  end
  object GroupBox5: TGroupBox
    Left = 1008
    Top = 0
    Width = 272
    Height = 720
    TabOrder = 0
    object GroupBox1: TGroupBox
      Left = 82
      Top = 211
      Width = 190
      Height = 144
      Caption = 'Speed Control'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -13
      Font.Name = 'Tahoma'
      Font.Style = []
      ParentFont = False
      TabOrder = 0
      object Label2: TLabel
        Left = 19
        Top = 22
        Width = 57
        Height = 19
        Caption = 'Frames:'
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -16
        Font.Name = 'Tahoma'
        Font.Style = []
        ParentFont = False
      end
      object Label1: TLabel
        Left = 82
        Top = 22
        Width = 46
        Height = 19
        Caption = 'Label1'
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -16
        Font.Name = 'Tahoma'
        Font.Style = []
        ParentFont = False
      end
      object Label35: TLabel
        Left = 19
        Top = 80
        Width = 54
        Height = 19
        Caption = 'Gens/s:'
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -16
        Font.Name = 'Tahoma'
        Font.Style = []
        ParentFont = False
      end
      object Label34: TLabel
        Left = 82
        Top = 80
        Width = 55
        Height = 19
        Caption = 'Label34'
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -16
        Font.Name = 'Tahoma'
        Font.Style = []
        ParentFont = False
      end
      object Label36: TLabel
        Left = 146
        Top = 105
        Width = 38
        Height = 19
        Caption = 'k=20'
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -16
        Font.Name = 'Tahoma'
        Font.Style = []
        ParentFont = False
      end
      object TrackBar3: TTrackBar
        Left = 0
        Top = 47
        Width = 185
        Height = 27
        Max = 100
        Min = 1
        Position = 100
        TabOrder = 0
        OnChange = TrackBar3Change
      end
      object TrackBar4: TTrackBar
        Left = 0
        Top = 105
        Width = 150
        Height = 27
        Max = 99
        Min = 1
        PageSize = 1
        Position = 1
        TabOrder = 1
        OnChange = TrackBar4Change
      end
    end
    object GroupBox2: TGroupBox
      Left = 0
      Top = 0
      Width = 272
      Height = 211
      Caption = 'Main Control'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -13
      Font.Name = 'Tahoma'
      Font.Style = []
      ParentFont = False
      TabOrder = 1
      OnMouseDown = GroupBox2MouseDown
      OnMouseMove = GroupBox2MouseMove
      OnMouseUp = GroupBox2MouseUp
      object Label5: TLabel
        Left = 32
        Top = 20
        Width = 45
        Height = 19
        Alignment = taRightJustify
        Caption = '400->'
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -16
        Font.Name = 'Tahoma'
        Font.Style = []
        ParentFont = False
      end
      object Label37: TLabel
        Left = 6
        Top = 155
        Width = 58
        Height = 19
        Caption = 'Y=1000'
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -16
        Font.Name = 'Tahoma'
        Font.Style = []
        ParentFont = False
      end
      object Label38: TLabel
        Left = 6
        Top = 178
        Width = 57
        Height = 19
        Caption = 'X=1000'
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -16
        Font.Name = 'Tahoma'
        Font.Style = []
        ParentFont = False
      end
      object Button2: TButton
        Left = 180
        Top = 111
        Width = 86
        Height = 25
        Caption = 'Next Gen'
        TabOrder = 0
        OnClick = Button2Click
      end
      object Button3: TButton
        Left = 180
        Top = 18
        Width = 86
        Height = 25
        Caption = 'Clear'
        TabOrder = 1
        OnClick = Button3Click
      end
      object Button5: TButton
        Left = 180
        Top = 80
        Width = 86
        Height = 25
        Caption = 'Cell Size: 3'
        TabOrder = 2
        OnClick = Button5Click
      end
      object Button6: TButton
        Left = 180
        Top = 173
        Width = 86
        Height = 25
        Caption = 'Fullscreen'
        TabOrder = 3
        OnClick = Button6Click
      end
      object Button9: TButton
        Left = 180
        Top = 49
        Width = 86
        Height = 25
        Caption = '-> .bmp'
        TabOrder = 4
        OnClick = Button9Click
      end
      object CheckBox5: TCheckBox
        Left = 82
        Top = 116
        Width = 86
        Height = 20
        BiDiMode = bdLeftToRight
        Caption = 'Grid'
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -16
        Font.Name = 'Tahoma'
        Font.Style = []
        ParentBiDiMode = False
        ParentFont = False
        TabOrder = 5
        OnClick = CheckBox2Click
      end
      object CheckBox3: TCheckBox
        Left = 197
        Top = 145
        Width = 86
        Height = 20
        BiDiMode = bdLeftToRight
        Caption = 'Auto'
        Checked = True
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -16
        Font.Name = 'Tahoma'
        Font.Style = []
        ParentBiDiMode = False
        ParentFont = False
        State = cbChecked
        TabOrder = 6
      end
      object CheckBox1: TCheckBox
        Left = 82
        Top = 22
        Width = 86
        Height = 20
        Caption = 'Random'
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -16
        Font.Name = 'Tahoma'
        Font.Style = []
        ParentFont = False
        TabOrder = 7
      end
      object CheckBox2: TCheckBox
        Left = 82
        Top = 138
        Width = 86
        Height = 20
        Caption = 'Effect 8'
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -16
        Font.Name = 'Tahoma'
        Font.Style = []
        ParentFont = False
        TabOrder = 8
        OnClick = CheckBox2Click
      end
      object CheckBox4: TCheckBox
        Left = 82
        Top = 160
        Width = 86
        Height = 20
        Caption = ' ( Alt )'
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -16
        Font.Name = 'Tahoma'
        Font.Style = []
        ParentFont = False
        TabOrder = 9
        OnClick = CheckBox2Click
      end
      object TrackBar1: TTrackBar
        Left = 73
        Top = 179
        Width = 107
        Height = 25
        Max = 9
        Min = 1
        PageSize = 1
        Position = 8
        TabOrder = 10
        OnChange = TrackBar1Change
      end
      object CheckBox6: TCheckBox
        Left = 82
        Top = 88
        Width = 86
        Height = 20
        Caption = 'Collisions'
        Checked = True
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -16
        Font.Name = 'Tahoma'
        Font.Style = []
        ParentFont = False
        State = cbChecked
        TabOrder = 11
      end
      object TrackBar2: TTrackBar
        Left = 40
        Top = 36
        Width = 27
        Height = 120
        LineSize = 10
        Max = 299
        Orientation = trVertical
        PageSize = 10
        Frequency = 10
        Position = 80
        TabOrder = 12
        OnChange = TrackBar2Change
      end
      object CheckBox7: TCheckBox
        Left = 82
        Top = 44
        Width = 95
        Height = 20
        Caption = 'gr.1 DryLife'
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -15
        Font.Name = 'Tahoma'
        Font.Style = []
        ParentFont = False
        TabOrder = 13
      end
      object CheckBox8: TCheckBox
        Left = 82
        Top = 66
        Width = 95
        Height = 20
        Caption = 'gr.2 DryLife'
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -15
        Font.Name = 'Tahoma'
        Font.Style = []
        ParentFont = False
        TabOrder = 14
      end
    end
    object GroupBox3: TGroupBox
      Left = 82
      Top = 487
      Width = 190
      Height = 195
      Caption = 'Stat'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -13
      Font.Name = 'Tahoma'
      Font.Style = []
      ParentFont = False
      TabOrder = 2
      object Label4: TLabel
        Left = 14
        Top = 19
        Width = 83
        Height = 19
        Caption = 'Generation:'
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -16
        Font.Name = 'Tahoma'
        Font.Style = []
        ParentFont = False
      end
      object Label3: TLabel
        Left = 103
        Top = 19
        Width = 46
        Height = 19
        Caption = 'Label1'
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -16
        Font.Name = 'Tahoma'
        Font.Style = []
        ParentFont = False
      end
      object Label6: TLabel
        Left = 11
        Top = 45
        Width = 40
        Height = 13
        Caption = 'Orange:'
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -11
        Font.Name = 'Tahoma'
        Font.Style = []
        ParentFont = False
      end
      object Label7: TLabel
        Left = 11
        Top = 64
        Width = 23
        Height = 13
        Caption = 'Red:'
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -11
        Font.Name = 'Tahoma'
        Font.Style = []
        ParentFont = False
      end
      object Label8: TLabel
        Left = 11
        Top = 83
        Width = 34
        Height = 13
        Caption = 'Yellow:'
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -11
        Font.Name = 'Tahoma'
        Font.Style = []
        ParentFont = False
      end
      object Label9: TLabel
        Left = 11
        Top = 102
        Width = 46
        Height = 13
        Caption = 'Magenta:'
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -11
        Font.Name = 'Tahoma'
        Font.Style = []
        ParentFont = False
      end
      object Label14: TLabel
        Left = 11
        Top = 121
        Width = 17
        Height = 13
        Caption = 'All:'
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -11
        Font.Name = 'Tahoma'
        Font.Style = [fsBold]
        ParentFont = False
      end
      object Label10: TLabel
        Left = 60
        Top = 45
        Width = 31
        Height = 13
        Caption = 'Label1'
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -11
        Font.Name = 'Tahoma'
        Font.Style = []
        ParentFont = False
      end
      object Label11: TLabel
        Left = 60
        Top = 64
        Width = 31
        Height = 13
        Caption = 'Label1'
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -11
        Font.Name = 'Tahoma'
        Font.Style = []
        ParentFont = False
      end
      object Label12: TLabel
        Left = 60
        Top = 83
        Width = 31
        Height = 13
        Caption = 'Label1'
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -11
        Font.Name = 'Tahoma'
        Font.Style = []
        ParentFont = False
      end
      object Label13: TLabel
        Left = 60
        Top = 102
        Width = 31
        Height = 13
        Caption = 'Label1'
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -11
        Font.Name = 'Tahoma'
        Font.Style = []
        ParentFont = False
      end
      object Label15: TLabel
        Left = 34
        Top = 121
        Width = 37
        Height = 13
        Caption = 'Label1'
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -11
        Font.Name = 'Tahoma'
        Font.Style = [fsBold]
        ParentFont = False
      end
      object Label16: TLabel
        Left = 105
        Top = 45
        Width = 29
        Height = 13
        Caption = 'Cyan:'
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -11
        Font.Name = 'Tahoma'
        Font.Style = []
        ParentFont = False
      end
      object Label17: TLabel
        Left = 105
        Top = 64
        Width = 28
        Height = 13
        Caption = 'Black:'
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -11
        Font.Name = 'Tahoma'
        Font.Style = []
        ParentFont = False
      end
      object Label18: TLabel
        Left = 105
        Top = 83
        Width = 33
        Height = 13
        Caption = 'Green:'
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -11
        Font.Name = 'Tahoma'
        Font.Style = []
        ParentFont = False
      end
      object Label19: TLabel
        Left = 105
        Top = 102
        Width = 34
        Height = 13
        Caption = 'Purple:'
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -11
        Font.Name = 'Tahoma'
        Font.Style = []
        ParentFont = False
      end
      object Label20: TLabel
        Left = 105
        Top = 121
        Width = 25
        Height = 13
        Caption = 'AAll:'
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -11
        Font.Name = 'Tahoma'
        Font.Style = [fsBold]
        ParentFont = False
      end
      object Label21: TLabel
        Left = 143
        Top = 45
        Width = 31
        Height = 13
        Caption = 'Label1'
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -11
        Font.Name = 'Tahoma'
        Font.Style = []
        ParentFont = False
      end
      object Label22: TLabel
        Left = 143
        Top = 64
        Width = 31
        Height = 13
        Caption = 'Label1'
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -11
        Font.Name = 'Tahoma'
        Font.Style = []
        ParentFont = False
      end
      object Label23: TLabel
        Left = 143
        Top = 83
        Width = 31
        Height = 13
        Caption = 'Label1'
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -11
        Font.Name = 'Tahoma'
        Font.Style = []
        ParentFont = False
      end
      object Label24: TLabel
        Left = 143
        Top = 102
        Width = 31
        Height = 13
        Caption = 'Label1'
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -11
        Font.Name = 'Tahoma'
        Font.Style = []
        ParentFont = False
      end
      object Label25: TLabel
        Left = 136
        Top = 121
        Width = 37
        Height = 13
        Caption = 'Label1'
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -11
        Font.Name = 'Tahoma'
        Font.Style = [fsBold]
        ParentFont = False
      end
      object Label26: TLabel
        Left = 11
        Top = 157
        Width = 30
        Height = 13
        Caption = 'Coll 2:'
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -11
        Font.Name = 'Tahoma'
        Font.Style = []
        ParentFont = False
      end
      object Label28: TLabel
        Left = 11
        Top = 172
        Width = 30
        Height = 13
        Caption = 'Coll 4:'
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -11
        Font.Name = 'Tahoma'
        Font.Style = []
        ParentFont = False
      end
      object Label30: TLabel
        Left = 47
        Top = 157
        Width = 31
        Height = 13
        Caption = 'Label1'
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -11
        Font.Name = 'Tahoma'
        Font.Style = []
        ParentFont = False
      end
      object Label32: TLabel
        Left = 47
        Top = 172
        Width = 31
        Height = 13
        Caption = 'Label1'
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -11
        Font.Name = 'Tahoma'
        Font.Style = []
        ParentFont = False
      end
      object Label27: TLabel
        Left = 99
        Top = 157
        Width = 30
        Height = 13
        Caption = 'Coll 3:'
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -11
        Font.Name = 'Tahoma'
        Font.Style = []
        ParentFont = False
      end
      object Label29: TLabel
        Left = 99
        Top = 172
        Width = 38
        Height = 13
        Caption = 'Coll >4:'
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -11
        Font.Name = 'Tahoma'
        Font.Style = []
        ParentFont = False
      end
      object Label31: TLabel
        Left = 143
        Top = 157
        Width = 31
        Height = 13
        Caption = 'Label1'
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -11
        Font.Name = 'Tahoma'
        Font.Style = []
        ParentFont = False
      end
      object Label33: TLabel
        Left = 143
        Top = 172
        Width = 31
        Height = 13
        Caption = 'Label1'
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -11
        Font.Name = 'Tahoma'
        Font.Style = []
        ParentFont = False
      end
      object Label39: TLabel
        Left = 34
        Top = 135
        Width = 44
        Height = 13
        Caption = 'Label39'
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -11
        Font.Name = 'Tahoma'
        Font.Style = [fsBold]
        ParentFont = False
      end
      object Label40: TLabel
        Left = 136
        Top = 135
        Width = 44
        Height = 13
        Caption = 'Label39'
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -11
        Font.Name = 'Tahoma'
        Font.Style = [fsBold]
        ParentFont = False
      end
    end
    object GroupBox4: TGroupBox
      Left = 0
      Top = 203
      Width = 83
      Height = 515
      Caption = 'Patterns'
      TabOrder = 3
      object SpeedButton1: TSpeedButton
        Left = 0
        Top = 18
        Width = 83
        Height = 30
        AllowAllUp = True
        GroupIndex = 1
        Caption = '1. Block'
        Font.Charset = RUSSIAN_CHARSET
        Font.Color = clBlack
        Font.Height = -11
        Font.Name = 'Tahoma'
        Font.Style = []
        ParentFont = False
        OnClick = SpeedButton1Click
        OnMouseUp = SpeedButton1MouseUp
      end
      object SpeedButton2: TSpeedButton
        Tag = 10
        Left = 0
        Top = 54
        Width = 83
        Height = 30
        AllowAllUp = True
        GroupIndex = 1
        Caption = '1. Blinker'
        Font.Charset = RUSSIAN_CHARSET
        Font.Color = clBlack
        Font.Height = -11
        Font.Name = 'Tahoma'
        Font.Style = []
        ParentFont = False
        OnClick = SpeedButton1Click
        OnMouseUp = SpeedButton1MouseUp
      end
      object SpeedButton3: TSpeedButton
        Tag = 20
        Left = 0
        Top = 90
        Width = 83
        Height = 30
        AllowAllUp = True
        GroupIndex = 1
        Caption = '1. Glider'
        Font.Charset = RUSSIAN_CHARSET
        Font.Color = clBlack
        Font.Height = -11
        Font.Name = 'Tahoma'
        Font.Style = []
        ParentFont = False
        OnClick = SpeedButton1Click
        OnMouseUp = SpeedButton1MouseUp
      end
      object SpeedButton4: TSpeedButton
        Tag = 30
        Left = 0
        Top = 126
        Width = 83
        Height = 30
        AllowAllUp = True
        GroupIndex = 1
        Caption = '1. Gosper gun'
        Font.Charset = RUSSIAN_CHARSET
        Font.Color = clBlack
        Font.Height = -11
        Font.Name = 'Tahoma'
        Font.Style = []
        ParentFont = False
        OnClick = SpeedButton1Click
        OnMouseUp = SpeedButton1MouseUp
      end
      object SpeedButton5: TSpeedButton
        Tag = 40
        Left = 0
        Top = 485
        Width = 83
        Height = 30
        AllowAllUp = True
        Caption = 'Auto Pattern 1'
        Font.Charset = RUSSIAN_CHARSET
        Font.Color = clRed
        Font.Height = -11
        Font.Name = 'Tahoma'
        Font.Style = []
        ParentFont = False
        OnClick = SpeedButton5Click
        OnMouseUp = SpeedButton5MouseUp
      end
      object SpeedButton6: TSpeedButton
        Tag = 50
        Left = 0
        Top = 162
        Width = 83
        Height = 30
        AllowAllUp = True
        GroupIndex = 1
        Caption = 'Paste (Save)'
        Font.Charset = RUSSIAN_CHARSET
        Font.Color = clGreen
        Font.Height = -11
        Font.Name = 'Tahoma'
        Font.Style = []
        ParentFont = False
        OnMouseUp = SpeedButton6MouseUp
      end
      object SpeedButton7: TSpeedButton
        Tag = 60
        Left = 0
        Top = 234
        Width = 83
        Height = 30
        AllowAllUp = True
        GroupIndex = 1
        Caption = 'Load...'
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clBlue
        Font.Height = -11
        Font.Name = 'Tahoma'
        Font.Style = []
        ParentFont = False
        OnClick = SpeedButton7Click
        OnMouseUp = SpeedButton7MouseUp
      end
      object SpeedButton8: TSpeedButton
        Tag = 61
        Left = 0
        Top = 270
        Width = 83
        Height = 30
        AllowAllUp = True
        GroupIndex = 1
        Caption = 'Load...'
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clBlue
        Font.Height = -11
        Font.Name = 'Tahoma'
        Font.Style = []
        ParentFont = False
        OnClick = SpeedButton7Click
        OnMouseUp = SpeedButton7MouseUp
      end
      object SpeedButton9: TSpeedButton
        Tag = 62
        Left = 0
        Top = 306
        Width = 83
        Height = 30
        AllowAllUp = True
        GroupIndex = 1
        Caption = 'Load...'
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clBlue
        Font.Height = -11
        Font.Name = 'Tahoma'
        Font.Style = []
        ParentFont = False
        OnClick = SpeedButton7Click
        OnMouseUp = SpeedButton7MouseUp
      end
      object SpeedButton10: TSpeedButton
        Tag = 63
        Left = 0
        Top = 342
        Width = 83
        Height = 30
        AllowAllUp = True
        GroupIndex = 1
        Caption = 'Load...'
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clBlue
        Font.Height = -11
        Font.Name = 'Tahoma'
        Font.Style = []
        ParentFont = False
        OnClick = SpeedButton7Click
        OnMouseUp = SpeedButton7MouseUp
      end
      object SpeedButton11: TSpeedButton
        Tag = 64
        Left = 0
        Top = 378
        Width = 83
        Height = 30
        AllowAllUp = True
        GroupIndex = 1
        Caption = 'Load...'
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clBlue
        Font.Height = -11
        Font.Name = 'Tahoma'
        Font.Style = []
        ParentFont = False
        OnClick = SpeedButton7Click
        OnMouseUp = SpeedButton7MouseUp
      end
      object SpeedButton12: TSpeedButton
        Tag = 65
        Left = 0
        Top = 413
        Width = 83
        Height = 30
        AllowAllUp = True
        GroupIndex = 1
        Caption = 'Load...'
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clBlue
        Font.Height = -11
        Font.Name = 'Tahoma'
        Font.Style = []
        ParentFont = False
        OnClick = SpeedButton7Click
        OnMouseUp = SpeedButton7MouseUp
      end
      object SpeedButton13: TSpeedButton
        Tag = 66
        Left = 0
        Top = 449
        Width = 83
        Height = 30
        AllowAllUp = True
        GroupIndex = 1
        Caption = 'Load...'
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clBlue
        Font.Height = -11
        Font.Name = 'Tahoma'
        Font.Style = []
        ParentFont = False
        OnClick = SpeedButton7Click
        OnMouseUp = SpeedButton7MouseUp
      end
      object SpeedButton14: TSpeedButton
        Tag = 67
        Left = 0
        Top = 198
        Width = 83
        Height = 30
        AllowAllUp = True
        GroupIndex = 1
        Caption = 'Load...'
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clBlue
        Font.Height = -11
        Font.Name = 'Tahoma'
        Font.Style = []
        ParentFont = False
        OnClick = SpeedButton7Click
        OnMouseUp = SpeedButton7MouseUp
      end
    end
    object RadioGroup1: TRadioGroup
      Left = 82
      Top = 355
      Width = 95
      Height = 135
      Caption = 'Left Mouse key'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'Tahoma'
      Font.Style = []
      ItemIndex = 0
      Items.Strings = (
        'Set Orange'
        'Set Red'
        'Set Yellow'
        'Set Magenta'
        'Set rand gr.1'
        'Select')
      ParentFont = False
      TabOrder = 4
    end
    object RadioGroup2: TRadioGroup
      Left = 176
      Top = 355
      Width = 95
      Height = 135
      Caption = 'Right Mouse key'
      Ctl3D = True
      ItemIndex = 5
      Items.Strings = (
        'Set Cyan'
        'Set Black'
        'Set Green'
        'Set Purple'
        'Set rand gr.2'
        'Clear Cell')
      ParentCtl3D = False
      TabOrder = 5
    end
    object Button7: TButton
      Left = 180
      Top = 688
      Width = 86
      Height = 25
      Caption = 'About'
      TabOrder = 6
      OnClick = Button7Click
    end
    object Button8: TButton
      Left = 88
      Top = 688
      Width = 86
      Height = 25
      Caption = 'Help'
      TabOrder = 7
      OnClick = Button8Click
    end
  end
  object Timer1: TTimer
    Interval = 10
    OnTimer = Timer1Timer
    Left = 968
    Top = 200
  end
  object Timer2: TTimer
    Interval = 500
    OnTimer = Timer2Timer
    Left = 968
    Top = 256
  end
  object OpenDialog1: TOpenDialog
    Filter = 
      'All Life files|*.cells;*.rle|Plaintext(*.cells)|*.cells|RLE(*.rl' +
      'e)|*.rle'
    Left = 968
    Top = 320
  end
  object SaveDialog1: TSaveDialog
    Filter = 'Plaintext(*.cells)|*.cells'
    Left = 944
    Top = 384
  end
end
