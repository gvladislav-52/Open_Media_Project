#ifndef FILE_PROCESSING_H
#define FILE_PROCESSING_H

#include <QObject>

class File_processing: public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString file_one READ getfile_one WRITE setFile_one NOTIFY file_oneChanged FINAL)
    Q_PROPERTY(QString file_two READ getfile_two WRITE setFile_two NOTIFY file_twoChanged FINAL)
public:
    File_processing();

    QString getfile_one() const;
    void setFile_one(const QString &newFile_one);

    QString getfile_two() const;
    void setFile_two(const QString &newFile_two);
    bool compare_files(const QString& file1, const QString& file2);

signals:

    void file_oneChanged();

    void file_twoChanged();

public slots:
    void openFile_one();
    void openFile_two();
    void file_srav();

private:
    QString m_file_one;
    QString m_file_two;

    QString get_file_hash(const QString& filename);
};

#endif // FILE_PROCESSING_H
