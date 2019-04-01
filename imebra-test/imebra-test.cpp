// imebra-test.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//
#include <imebra/imebra.h>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <map>

// ageId = 4112

int main(int argc, const char* argv[])
{
	const auto path = "d:/korotkov/DICOM/17020708/29510000/80509054";
	const auto loadedDataSet = std::unique_ptr<imebra::DataSet>(imebra::CodecFactory::load(path));
	auto tags = loadedDataSet->getTags();

	std::map<int, std::wstring> tagMap{};
	for (const auto& tag : tags)
	{
		auto buf = std::wstringstream{};
		try
		{
			const auto key = tag.getTagId();
			buf << imebra::DicomDictionary::getUnicodeTagName(tag) << " : "
				<< loadedDataSet->getUnicodeString(tag, 0, L"");
			const auto val = buf.str();
			tagMap[key] = val;
		}
		catch (...)
		{
		}

	}

	int count = 0;
	for (const auto& [k, v] : tagMap)
	{
		std::wcout << k << ".\t" << v << '\n';
		count++;
	}
	std::wcout << L"size = " << count << L"\n";
	
	////////////////////////////////////////////////////////////

	count = 0;
	for (const auto& tag : tags)
	{
		auto buf = std::wstringstream{};
		try
		{
			const auto key = std::to_wstring(tag.getGroupId()) 
				    + L"_" + std::to_wstring(tag.getGroupOrder())
				    + L"_" + std::to_wstring(tag.getTagId());
			buf << imebra::DicomDictionary::getUnicodeTagName(tag) << " : "
				<< loadedDataSet->getUnicodeString(tag, 0, L"");
			const auto val = buf.str();
			std::wcout << key << L".\t" << buf.str() << L'\n';
		}
		catch (...)
		{
		}
		count++;
	}
	std::wcout << L"size = " << count << L"\n";
	//imebra::DicomDictionary dictionary{};
}
