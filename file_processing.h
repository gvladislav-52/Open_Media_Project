#ifndef FILE_PROCESSING_H
#define FILE_PROCESSING_H

#include <QObject>

class File_processing: public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString file_one READ getfile_one WRITE setFile_one NOTIFY file_oneChanged FINAL)
    Q_PROPERTY(QString file_two READ getfile_two WRITE setFile_two NOTIFY file_twoChanged FINAL)
    Q_PROPERTY(QVector<QString> vector_Duplicates READ getvector_Duplicates WRITE setVector_Duplicates NOTIFY vector_DuplicatesChanged FINAL)
public:
    File_processing();

    QString getfile_one() const;
    QString getfile_two() const;
    QVector<QString> getvector_Duplicates() const;

    void setFile_one(const QString &newFile_one);
    void setFile_two(const QString &newFile_two);
    void setVector(const QString &file);
    void setVector_Duplicates(const QVector<QString> &newVector_Duplicates);

signals:
    void file_oneChanged();
    void file_twoChanged();
    void vector_DuplicatesChanged();

public slots:
    void openFile_one();
    void openFile_two();
    void findDuplicates();


private:
    QString m_file_one;
    QString m_file_two;

    bool compareFiles(const QString& file1, const QString& file2);
    QVector<QString> m_vector_Duplicates;
    void clearVector();
};

#endif // FILE_PROCESSING_H
