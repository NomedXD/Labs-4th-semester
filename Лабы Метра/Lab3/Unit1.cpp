// ---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Unit1.h"
#include "Unit2.cpp"
#include <string>
#include <stdio.h>
// ---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"

TForm1 *Form1;
String txt;

// ---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner) : TForm(Owner) {

}

// ---------------------------------------------------------------------------
void __fastcall TForm1::BLoadClick(TObject *Sender) {
	if (TForm1::OpenDialog1->Execute()) {
		txt = OpenDialog1->FileName;
		if (in.is_open())
			in.close();
		in.open(txt.c_str());
		TForm1::Memo1->Lines->Clear();
		TForm1::Memo1->Lines->LoadFromFile(TForm1::OpenDialog1->FileName);
	}
}

// ---------------------------------------------------------------------------
void __fastcall TForm1::Button2Click(TObject *Sender) {
	if (in.is_open()) {
		in.close();
		in.open(txt.c_str());
	}
	LError->Visible = false;
	next = 0;
	errorFlag = false;
	spans.clear();
	P.clear();
	M.clear();
	C.clear();
	T.clear();
	IOPMCT.clear();
	IOP.clear();
	IOM.clear();
	IOC.clear();
	IOT.clear();
	terms.clear();

	if (getTerms()) {
		if (!mainBlock()) {
			LError->Visible = true;
		}
		else {
			Memo2->Lines->Clear();
			Memo3->Lines->Clear();
			Memo4->Lines->Clear();
			const char* s1 = "\t";
			const char* s2 = "\n";
			const char* s3 = "\n\n\n";
			int resultSpan = 0;
			for (const auto&elem : spans) {
				char str[12];
				sprintf(str, "%d", elem.second);
				resultSpan += elem.second;
				char res[100];
				strcpy(res, elem.first.c_str());
				strcat(res, s1);
				strcat(res, str);
				strcat(res, s2);
				Memo2->Lines->Add(res);
			}
			char str[100];
			sprintf(str, "|S = %d|", resultSpan);
			Memo2->Lines->Add(str);

			const char* s4 = "P:\n";
			const char* s5 = "M:\n";
			const char* s6 = "C:\n";
			const char* s7 = "T:\n";
			Memo3->Lines->Add(s4);
			for (const auto&elem : P) {

				char str[12];
				sprintf(str, "%d", elem.second);
				char res[100];
				strcpy(res, elem.first.c_str());
				strcat(res, s1);
				strcat(res, str);
				strcat(res, s2);
				strcat(res, s3);
				Memo3->Lines->Add(res);
			}
			char str11[100];
			sprintf(str11, "<p = %d>", P.size());
			Memo3->Lines->Add(str11);

			Memo3->Lines->Add(s3);
			Memo3->Lines->Add(s5);
			for (const auto&elem : M) {

				char str[12];
				sprintf(str, "%d", elem.second);
				char res[100];
				strcpy(res, elem.first.c_str());
				strcat(res, s1);
				strcat(res, str);
				strcat(res, s2);
				strcat(res, s3);
				Memo3->Lines->Add(res);
			}
			char str2[100];
			sprintf(str2, "<m = %d>", M.size());
			Memo3->Lines->Add(str2);

			Memo3->Lines->Add(s3);
			Memo3->Lines->Add(s6);
			for (const auto&elem : C) {

				char str[12];
				sprintf(str, "%d", elem.second);
				char res[100];
				strcpy(res, elem.first.c_str());
				strcat(res, s1);
				strcat(res, str);
				strcat(res, s2);
				strcat(res, s3);
				Memo3->Lines->Add(res);
			}
			char str3[100];
			sprintf(str3, "<c = %d>", C.size());
			Memo3->Lines->Add(str3);

			Memo3->Lines->Add(s3);
			Memo3->Lines->Add(s7);
			for (const auto&elem : T) {

				char str[12];
				sprintf(str, "%d", elem.second);
				char res[100];
				strcpy(res, elem.first.c_str());
				strcat(res, s1);
				strcat(res, str);
				strcat(res, s2);
				strcat(res, s3);
				Memo3->Lines->Add(res);
			}
			char str4[100];
			sprintf(str4, "<t = %d>", T.size());
			Memo3->Lines->Add(str4);
			char str5[100];
			sprintf(str5, "|Q = %lf|", getPMCT_Q(P, M, C, T));
			Memo3->Lines->Add(str5);

			const char* s8 = "IOP:\n";
			const char* s9 = "IOM:\n";
			const char* s10 = "IOC:\n";
			const char* s11 = "IOT:\n";
			Memo4->Lines->Add(s8);
			for (const auto&elem : IOP) {

				char str[12];
				sprintf(str, "%d", elem.second);
				char res[100];
				strcpy(res, elem.first.c_str());
				strcat(res, s1);
				strcat(res, str);
				strcat(res, s2);
				strcat(res, s3);
				Memo4->Lines->Add(res);
			}
			char str6[100];
			sprintf(str6, "<p = %d>", IOP.size());
			Memo4->Lines->Add(str6);

			Memo4->Lines->Add(s3);
			Memo4->Lines->Add(s9);
			for (const auto&elem : IOM) {

				char str[12];
				sprintf(str, "%d", elem.second);
				char res[100];
				strcpy(res, elem.first.c_str());
				strcat(res, s1);
				strcat(res, str);
				strcat(res, s2);
				strcat(res, s3);
				Memo4->Lines->Add(res);
			}
			char str7[100];
			sprintf(str7, "<m = %d>", IOM.size());
			Memo4->Lines->Add(str7);

			Memo4->Lines->Add(s3);
			Memo4->Lines->Add(s10);
			for (const auto&elem : IOC) {

				char str[12];
				sprintf(str, "%d", elem.second);
				char res[100];
				strcpy(res, elem.first.c_str());
				strcat(res, s1);
				strcat(res, str);
				strcat(res, s2);
				strcat(res, s3);
				Memo4->Lines->Add(res);
			}
			char str8[100];
			sprintf(str8, "<c = %d>", IOC.size());
			Memo4->Lines->Add(str8);

			Memo4->Lines->Add(s3);
			Memo4->Lines->Add(s11);
			for (const auto&elem : IOT) {
				char str[12];
				sprintf(str, "%d", elem.second);
				char res[100];
				strcpy(res, elem.first.c_str());
				strcat(res, s1);
				strcat(res, str);
				strcat(res, s2);
				strcat(res, s3);
				Memo4->Lines->Add(s3);
				Memo4->Lines->Add(res);
			}
			char str9[100];
			sprintf(str9, "<t = %d>", IOT.size());
			Memo4->Lines->Add(str9);
			char str10[100];
			sprintf(str10, "|Q = %lf|", getPMCT_Q(IOP, IOM, IOC, IOT));
			Memo4->Lines->Add(str10);
		}
	}
}

// ---------------------------------------------------------------------------

void __fastcall TForm1::Button1Click(TObject *Sender) {
	if (TForm1::SaveDialog1->Execute()) {
		txt = SaveDialog1->FileName;
		FILE *f;
		if ((f = fopen(AnsiString(txt).c_str(), "w")) != NULL) {
			fprintf(f,"SPANS:\n");
			for (const auto&elem : spans)
				fprintf(f,"%s\t%d\n",elem.first.c_str(),elem.second);


			fprintf(f,"\n\n\n");

			fprintf(f,"P:\n");
			for (const auto&elem : P)
				fprintf(f,"%s\t%d\n",elem.first.c_str(),elem.second);

			fprintf(f,"\n\n\n");

			fprintf(f,"M:\n");
			for (const auto&elem : M)
				fprintf(f,"%s\t%d\n",elem.first.c_str(),elem.second);

			fprintf(f,"\n\n\n");

			fprintf(f,"C:\n");
			for (const auto&elem : C)
				fprintf(f,"%s\t%d\n",elem.first.c_str(),elem.second);

			fprintf(f,"\n\n\n");

			fprintf(f,"T:\n");
			for (const auto&elem : T)
				fprintf(f,"%s\t%d\n",elem.first.c_str(),elem.second);

			fprintf(f,"\n\n\n");

			fprintf(f,"IOP:\n");
			for (const auto&elem : IOP)
				fprintf(f,"%s\t%d\n",elem.first.c_str(),elem.second);

			fprintf(f,"\n\n\n");

			fprintf(f,"IOM:\n");
			for (const auto&elem : IOM)
				fprintf(f,"%s\t%d\n",elem.first.c_str(),elem.second);

			fprintf(f,"\n\n\n");

			fprintf(f,"IOC:\n");
			for (const auto&elem : IOC)
				fprintf(f,"%s\t%d\n",elem.first.c_str(),elem.second);

			fprintf(f,"\n\n\n");

			fprintf(f,"IOT:\n");
			for (const auto&elem : IOT)
				fprintf(f,"%s\t%d\n",elem.first.c_str(),elem.second);
			fclose(f);
		}
	}
}
// ---------------------------------------------------------------------------
