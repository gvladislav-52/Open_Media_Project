#include "file_processing.h"
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

// Функция для получения хэша файла
QString File_processing::get_file_hash(const QString& filename) {
    QFile file(filename);
    if (!file.open(QIODevice::ReadOnly)) {
        return "";
    }

    // Используем простой алгоритм для демонстрации,
    // в реальном мире стоит использовать более надежный алгоритм (например, SHA-256)
    QByteArray hash_value;
    QByteArray buffer;
    while (!file.atEnd()) {
        buffer = file.read(1024);
        for (int i = 0; i < buffer.size(); ++i) {
            hash_value.append(buffer[i] % 128);
        }
    }
    file.close();

    return QString(hash_value.toHex());
}

// Функция для сравнения файлов
bool File_processing::compare_files(const QString& file1, const QString& file2) {
    return get_file_hash(file1) == get_file_hash(file2);
}

void File_processing::file_srav() {
    QStringList files1, files2;

    // Получение всех файлов из первой папки
    QDir dir1(m_file_one);
    for (const QString& file : dir1.entryList(QDir::Files)) {
        files1.append(dir1.absoluteFilePath(file));
    }

    // Получение всех файлов из второй папки
    QDir dir2(m_file_two);
    for (const QString& file : dir2.entryList(QDir::Files)) {
        files2.append(dir2.absoluteFilePath(file));
    }

    // Поиск дубликатов
    for (const QString& file1 : files1) {
        for (const QString& file2 : files2) {
            if (File_processing::compare_files(file1, file2)) {
                setVector(file1);
                break;
            }
        }
    }

    if (m_vector_Duplicates.isEmpty()) {
        qDebug() << "Дубликаты не найдены.";
    }
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

void File_processing::setVector(const QString &file)
{
    m_vector_Duplicates.append(file);
    emit vector_DuplicatesChanged();
}
