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
    QString folder1 = QFileDialog::getExistingDirectory(nullptr, "Выберите первую папку", QDir::homePath());
    QString folder2 = QFileDialog::getExistingDirectory(nullptr, "Выберите вторую папку", QDir::homePath());

    QStringList files1, files2;

    // Получение всех файлов из первой папки
    QDir dir1(folder1);
    for (const QString& file : dir1.entryList(QDir::Files)) {
        files1.append(dir1.absoluteFilePath(file));
    }

    // Получение всех файлов из второй папки
    QDir dir2(folder2);
    for (const QString& file : dir2.entryList(QDir::Files)) {
        files2.append(dir2.absoluteFilePath(file));
    }

    // Поиск дубликатов
    QStringList duplicates;
    for (const QString& file1 : files1) {
        for (const QString& file2 : files2) {
            if (File_processing::compare_files(file1, file2)) {
                duplicates.append(file1);
                duplicates.append(file2);
                break;
            }
        }
    }

    // Удаление дубликатов из списка (оставляем только уникальные пути)
    duplicates.removeDuplicates();

    // Вывод списка дубликатов
    if (!duplicates.isEmpty()) {
        qDebug() << "Найдены следующие дубликаты:";
        for (const QString& duplicate : duplicates) {
            qDebug() << duplicate;
        }
    } else {
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
