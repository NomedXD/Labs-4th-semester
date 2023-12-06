// ---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Unit1.h"
#include "Unit2.cpp"
#include <string>
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
		if(in.is_open())
			in.close();
		in.open(txt.c_str());
		TForm1::Memo1->Lines->Clear();
		TForm1::Memo1->Lines->LoadFromFile(TForm1::OpenDialog1->FileName);
	}
}

// ---------------------------------------------------------------------------
void __fastcall TForm1::Button2Click(TObject *Sender) {
	clearAll();
	Memo2->Lines->Clear();
	Memo3->Lines->Clear();
	Edit1->Clear();
	Edit2->Clear();
	Edit3->Clear();
	Edit4->Clear();
	Edit5->Clear();
	Edit6->Clear();
	Edit7->Clear();
	bool flag;
	if (in.is_open()) {

		next = 0;
		if (getTerms())
			if (!mainBlock2()) {
				Label1->Visible = true;
			}
			else {
				Label1->Visible = false;
				for (const auto&elem : operators)
					if (elem.second && elem.first != "") {
						std::string temp =
							elem.first + "\t" + std::to_string(elem.second);
						Memo2->Lines->Add(temp.c_str());
						operatorsCount += elem.second;
					}
					else
						operatorsVocabulary--;
				for (const auto&elem : operands)
					if (elem.second) {
						std::string temp =
							elem.first + "\t" + std::to_string(elem.second);
						Memo3->Lines->Add(temp.c_str());
						operandsCount += elem.second;
					}
				operatorsVocabulary += operators.size();
				operandsVocabulary = operands.size();
				programVocabulary = operatorsVocabulary + operandsVocabulary;
				programLength = operatorsCount + operandsCount;
				programVolume = programLength * (log(programVocabulary) / log(2));
				Edit1->Text = (std::to_string(operatorsVocabulary)).c_str();
				Edit3->Text = (std::to_string(operandsVocabulary)).c_str();
				Edit2->Text = (std::to_string(operatorsCount)).c_str();
				Edit4->Text = (std::to_string(operandsCount)).c_str();
				Edit5->Text = (std::to_string(programVocabulary)).c_str();
				Edit6->Text = (std::to_string(programLength)).c_str();
				Edit7->Text = (std::to_string(programVolume)).c_str();
			}


	}

}

// ---------------------------------------------------------------------------
void __fastcall TForm1::Button1Click(TObject *Sender) {

	if (TForm1::SaveDialog1->Execute()) {
		txt = SaveDialog1->FileName;
		out.open(txt.c_str());
		next = 0;
		Label1->Visible = false;
		out << "���������:\n";
		for (const auto&elem : operators)
			if (elem.second)
				out << elem.first << "\t" << elem.second << "\n";
		out << "������� ����������: " << operatorsVocabulary << "\n";
		out << "���������� ����������: " << operatorsCount << "\n";
		out << "\n\n\n";
		out << "��������:\n";
		for (const auto& elem : operands)
        if (elem.second)
				out << elem.first << "\t" << elem.second << "\n";
		out << "������� ���������: " << operandsVocabulary << "\n";
		out << "���������� ���������: " << operandsCount << "\n";

		out << "\n\n\n";
		out << "� �����:\n";
		out << "����� ������� ���������: " << programVocabulary << "\n";
		out << "����� ���������: " << programLength << "\n";
		out << "����� ���������: " << programVolume;
        out.close();
	}
}
// ---------------------------------------------------------------------------
