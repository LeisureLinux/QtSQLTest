# SqlTest
> *Change to languages : [English](README.en.md) , [Korean](README.md)*

- QSqlDatabase 기본클래스로 DB 접속과 데이터 확인 예제 입니다.
- MSSQL / MYSQL / SQLITE 를 사용할 수 있습니다.

## 테스트 환경
- Qt 5.12.3 / Windows10 / MSVC2017 32bit
- QtCreator

## 주의사항
- QtCreate에서 MYSQL 컴파일 시, driver not loaded. 에러가 발생하면, mysql 라이브러리파일을 추가해주세요.
- (https://dev.mysql.com/downloads/mysql/) 컴파일러 bit에 맞게 다운로드 합니다.
- 다운로드한 압축파일에서 libmysql.dll 과 libmysqld.dll 파일을 찾습니다.
- Qt가 설치된 경로 (ex)(c:/Qt/Qt.5.12.3/5.12.3/msvc2017/bin) 안에 libmysql.dll 과 libmysqld.dll 파일을 복사해주세요.
- 어플리케이션 배포 시 exe파일 경로에 libmysql.dll의 파일이 반드시 있어야합니다.






