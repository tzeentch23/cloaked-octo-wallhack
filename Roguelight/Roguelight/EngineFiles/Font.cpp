#include "stdafx.h"
#include "Font.h"


//---------------------------
// Font methods
//---------------------------
Font::Font(IDWriteTextFormat *textFormatPtr) : m_TextFormatPtr(textFormatPtr)
{}

Font::Font(const String& fontName, float size)
{
	tstring temp(fontName.C_str());
	std::wstring str(temp.begin(), temp.end());
	LoadTextFormat(str.c_str(), size);
}


Font::~Font(void)
{
	m_TextFormatPtr->Release();
}

void Font::LoadTextFormat(const wchar_t* fontName, float size)
{
	HRESULT hr;
	// Create a DirectWrite text format object.
	hr = GameEngine::GetSingleton()->GetDWriteFactory()->CreateTextFormat(fontName, NULL, DWRITE_FONT_WEIGHT_NORMAL, DWRITE_FONT_STYLE_NORMAL, DWRITE_FONT_STRETCH_NORMAL, size, L"", &m_TextFormatPtr);

	if (SUCCEEDED(hr))
	{
		// align left and top the text horizontally and vertically.
		m_TextFormatPtr->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_LEADING);
		m_TextFormatPtr->SetParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT_NEAR);
	}
	else
	{
		MessageBoxW(NULL, fontName, L"FONT BUILDING ERROR", MB_ICONERROR);
		exit(-1);
	}
}

IDWriteTextFormat* Font::GetTextFormat() const
{
	return m_TextFormatPtr;
}

void Font::SetAlignHLeft()
{
	m_TextFormatPtr->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_LEADING);
}

void Font::SetAlignHCenter()
{
	m_TextFormatPtr->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_CENTER);
}

void Font::SetAlignHRight()
{
	m_TextFormatPtr->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_TRAILING);
}

void Font::SetAlignVTop()
{
	m_TextFormatPtr->SetParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT_NEAR);
}

void Font::SetAlignVCenter()
{
	m_TextFormatPtr->SetParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT_CENTER);
}

void Font::SetAlignVBottom()
{
	m_TextFormatPtr->SetParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT_FAR);
}