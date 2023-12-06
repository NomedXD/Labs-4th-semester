program Project1;

uses
  Vcl.Forms,
  fMain in 'fMain.pas' {Form1},
  Vcl.Themes,
  Vcl.Styles;

{$R *.res}

begin
  Application.Initialize;
  Application.MainFormOnTaskbar := True;
  TStyleManager.TrySetStyle('Lavender Classico');
  Application.CreateForm(TfmMain, fmMain);
  Application.Run;
end.
