# SqlTest
> *언어 변환 : [영어](README.en.md) , [한국어](README.md)*

- This is an example of connecting to DB and checking data with QSqlDatabase basic class.
- You can use MSSQL/MYSQL/SQLITE.

## Tested Environment
- Qt 5.12.3 / Windows10 / MSVC2017 32bit
- QtCreator

## Caution
- If an error occurs(driver not loaded.) when compiling MYSQL in QtCreate, you must add the mysql library file.(libmysql.dll)
- (https://dev.mysql.com/downloads/mysql/) Download according to the compiler bit.
- Find the libmysql.dll and libmysqld.dll files in the downloaded file.
- Copy the files(libmysql.dll, libmysqld.dll) in Qt Path. ex) c:/Qt/Qt.5.12.3/5.12.3/msvc2017/bin
- When deploying an application, the file(libmysql.dll) must be present in .exe file path.