#include "file_processing.h"
#include <iostream>
#include "QFileDialog"

File_processing::File_processing()
{
    m_file_one = "-";
    m_file_two = "-";
}

void File_processing::openFile_one()
{
    setFile_one(QFileDialog::getExistingDirectory(nullptr, "Выберите папку", ""));
}

void File_processing::openFile_two()
{
    setFile_two(QFileDialog::getExistingDirectory(nullptr, "Выберите папку", ""));
}

bool File_processing::compareFiles(const QString& file1, const QString& file2) {
    QFile *file1Stream = new QFile(file1);
    QFile *file2Stream = new QFile(file2);

    if (!file1Stream->open(QIODevice::ReadOnly) || !file2Stream->open(QIODevice::ReadOnly)) {
        std::cerr << "Ошибка открытия файла: " << (file1Stream->isOpen() ? file2.toStdString() : file1.toStdString()) << std::endl;
        return false;
    }

    char char1, char2;
    while (true) {
        if (!file1Stream->getChar(&char1) || !file2Stream->getChar(&char2))
            return file1Stream->atEnd() == file2Stream->atEnd();
        if (char1 != char2)
            return false;
    }
    delete file2Stream;
    delete file1Stream;
}

void File_processing::findDuplicates() {
    if(!getvector_Duplicates().isEmpty())
        clearVector();
    QDir *directory1 = new QDir(m_file_one);
    QDir *directory2 = new QDir(m_file_two);

    if (!directory1->exists() || !directory2->exists()) {
        std::cerr << "Одна из указанных папок не существует." << std::endl;
    }

    for (const QFileInfo& fileInfo1 : directory1->entryInfoList(QDir::Files | QDir::NoDotAndDotDot | QDir::Hidden | QDir::System)) {
        QString filename1 = fileInfo1.absoluteFilePath();

        for (const QFileInfo& fileInfo2 : directory2->entryInfoList(QDir::Files | QDir::NoDotAndDotDot | QDir::Hidden | QDir::System)) {
            QString filename2 = fileInfo2.absoluteFilePath();

            if (compareFiles(filename1, filename2))
                setVector(filename1);
        }
    }
    delete directory2;
    delete directory1;
}

QString File_processing::getfile_one() const
{
    return m_file_one;
}

void File_processing::setFile_one(const QString &newFile_one)
{
    if (m_file_one == newFile_one)
        return;
    m_file_one = newFile_one;
    emit file_oneChanged();
}

QString File_processing::getfile_two() const
{
    return m_file_two;
}

void File_processing::setFile_two(const QString &newFile_two)
{
    if (m_file_two == newFile_two)
        return;
    m_file_two = newFile_two;
    emit file_twoChanged();
}

QVector<QString> File_processing::getvector_Duplicates() const
{
    return m_vector_Duplicates;
}

void File_processing::setVector_Duplicates(const QVector<QString> &newVector_Duplicates)
{
    if (m_vector_Duplicates == newVector_Duplicates)
        return;
    m_vector_Duplicates = newVector_Duplicates;
    emit vector_DuplicatesChanged();
}

void File_processing::clearVector()
{
    m_vector_Duplicates.clear();
}

void File_processing::setVector(const QString &file)
{
    m_vector_Duplicates.append(file);
    emit vector_DuplicatesChanged();
}
