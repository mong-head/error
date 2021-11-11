### 환경
* windows 10
### 문제
MySQL Workbench에서 3306 포트로 접속한 DB와 Node에서 개발하기 위해 Sequelize에서 3306 포트로 접속한 DB의 내용이 다른 것을 보고 MySQL이 2개가 깔려있고, 포트가 서로 충돌이 일어나서 일정하지 않게 프로그램에 따라 다른 DB로 연결되는 것을 알게 되었습니다. 

문제를 확인 하기 위해 작업 관리자를 틀어보니 실제로 예전에 깔았던 bitnami에서 함께 깔았던 MySQL과 Oracle에서 깐 MySQL이 함께 있는 것을 볼 수 있었습니다.
* 작업 관리자 화면
  ![](https://images.velog.io/images/mong-head/post/770a38de-a8ec-4138-9ff9-4f75ef24923e/K-065.jpg)
  * mysqld가 두 개가 있는 것을 볼 수 있습니다.
  * 하나는 bitnami를 통해 깐 MySQL이고, 다른 하나는 일반적으로 MySQL을 설치하는 방법인 Oracle 통한 MySQL 설치로 만들어진 MySQL server입니다.
  
### 해결
저는 제가 관리하기 쉬운 MySQL의 포트를 변경하기로 하였습니다. 따라서, 예전에 사용했던 bitnami말고 현재 사용하는 Oracle 홈페이지에서 설치한 MySQL의 포트를 변경합니다. 

DB의 설정파일은 my.ini파일에 있습니다. 따라서 윈도우 cmd창에서 my.ini파일을 찾아주었습니다. ```C:\```경로에서 ```dir /s my.ini```를 하시면 my.ini파일이 있는 것을 보실 수 있습니다.
![](https://images.velog.io/images/mong-head/post/b87e9f48-a39a-4d4e-a6f1-7aa84a0b2983/K-064.jpg)

전 여기에서 MySQL Server 8.0에 있는 my.ini파일의 포트를 변경해줄 것이기에 해당 경로 (```C:\ProgramData\MySQL\MySQL Server 8.0\my.ini```)의 my.ini파일을 틀고 port번호를 3306에서 3307로 변경해주었습니다. 두 군데에 있으니 두 군데 모두 변경해주시면 됩니다.

|변경 전|변경 후|
|:---:|:---:|
|![](https://images.velog.io/images/mong-head/post/f7d8d57b-f552-4648-944a-d6eceeb7fff0/K-066.jpg)|![](https://images.velog.io/images/mong-head/post/b7d5d07e-a362-49f4-bdf9-7ae4d2d58be9/K-067.jpg)|

그 이후, 변경한 MySQL의 서비스를 중지한 후, 다시 실행해야 합니다. 윈도우 버튼을 눌러 "서비스"를 검색하셔서 어플을 실행시켜주신 후, MySQL80의 서비스를 중지한 후 다시 실행을 하시면 됩니다.
![](https://images.velog.io/images/mong-head/post/bf2226b2-6056-4aa7-ba24-2a75019113c3/K-064.jpg)

