
Sequelize에서 foreign key를 설정하는 방법은 밑과 같습니다.

예를 들어, participant, chat table이 있을 때, participant : chat 의 관계가 1 : N 이라 가정하겠습니다. chat table은 participant의 primary key인 no를 participantNo라는 foreign key를 가집니다. 
![](https://images.velog.io/images/mong-head/post/01df71eb-90d8-47c8-9da6-e902d53fb224/K-063.jpg)

파일에 대해 설명드리자면, models라는 폴더 내에 index.js, Chat.js, Participant.js가 존재합니다.
Chat.js, Participant.js는 sequelize.define 함수로chat, participant table을 정의하는 파일이고, index.js는 sequelize 생성(DB연결) 및 Chat과 Participant등등 table들의 관계( relation)를 명시하는 파일입니다.

이때, chat sequelize define에는 foreign key를 명시하지 않고, index.js에서 chat과 participant의 관계를 명시하면 됩니다. 즉, 밑처럼 관계를 index.js에서 밑 부분만 추가하시면 됩니다.

> models/index.js

```js
...
Participant.hasMany(Chat, {
    foreignKey: 'participantNo',
    allowNull: false,
    constraints: true,
    onDelete: 'cascade'
});
Chat.belongsTo(Participant, {
    foreignKey: 'participantNo'
});
...
```


밑은 전체 코드입니다.

> models/index.js

```js
const { Sequelize, DataTypes } = require('sequelize');

const sequelize = new Sequelize(
    process.env.DB_NAME,
    process.env.DB_USER,
    process.env.DB_PASSWORD,{
        host: process.env.DB_HOST,
        port: process.env.DB_PORT,
        timezone: "+09:00",
        dialect: 'mysql'
    }
);

const Chat = require('./Chat')(sequelize);
const Participant = require('./Participant')(sequelize);

Participant.hasMany(Chat, {
    foreignKey: 'participantNo',
    allowNull: false,
    constraints: true,
    onDelete: 'cascade'
});
Chat.belongsTo(Participant, {
    foreignKey: 'participantNo'
});

Chat.sync({
    force: process.env.TABLE_CREATE_ALWAYS === 'true', // true : (drop) table 데이터 없어질 수 있음
    alter: process.env.TABLE_ALTER_SYNC === 'true'     // 개발 끝나면 false로 하기
})
Participant.sync({
    force: process.env.TABLE_CREATE_ALWAYS === 'true', // true : (drop) table 데이터 없어질 수 있음
    alter: process.env.TABLE_ALTER_SYNC === 'true'     // 개발 끝나면 false로 하기
})

module.exports = {sequelize, Chat, Participant};
```


> models/Participant.js

```js
const { Sequelize, DataTypes } = require('sequelize');
const models = require('../models');

module.exports = function(sequelize){
    // foreign Key : (Room)room_no, (User)user_no
    const participant = sequelize.define('Participant', {
        no: {
            field: 'no',
            type: DataTypes.INTEGER,
            primaryKey: true,
            autoIncrement: true,
            allowNull: false
        },
        role: {
            field: 'role',
            type: DataTypes.STRING(45),
            allowNull: false
        },
        status: {
            field: 'status',
            type: DataTypes.ENUM('true', 'false') ,
            allowNull: false
        },
        createdAt: {
            field: 'createdAt',
            type: DataTypes.DATE,
            allowNull: false
        },
        lastReadAt: {
            field: 'lastReadAt',
            type: DataTypes.DATE,
            allowNull: false
        }
    }, {
        underscored: false, // updateAt -> updateAt (underscored: update_at)
        freezeTableName: true,
        timestamps: true,
        createdAt: false,
        updatedAt: false,
        tableName: 'participant'
    });
    return participant;
}
```


> models/chat.js

```js
const { Sequelize, DataTypes } = require('sequelize');

module.exports = function(sequelize){
    // foreign Key : (Participant)participant_no
    return sequelize.define('Chat', {
        no: {
            field: 'no',
            type: DataTypes.INTEGER,
            primaryKey: true,
            autoIncrement: true,
            allowNull: false
        },
        type: {
            field: 'type',
            type: DataTypes.STRING(45),
            allowNull: false
        },
        createdAt: {
            field: 'createdAt',
            type: DataTypes.DATE,
            allowNull: false
        },
        contents: {
            field: 'contents',
            type: DataTypes.TEXT,
            allowNull: false
        },
        read: {
            field: 'read',
            type: DataTypes.INTEGER,
            allowNull: false
        }
    }, {
        underscored: false, // updateAt -> updateAt (underscored: update_at)
        freezeTableName: true,
        timestamps: true,
        createdAt: false,
        updatedAt: false,
        tableName: 'chat'
    });
}
```

### 결과
서버를 실행시키셨을 때, 밑처럼 실행된다면 성공입니다.
```shell
Executing (default): CREATE TABLE IF NOT EXISTS `chat` (`no` INTEGER NOT NULL auto_increment , `type` VARCHAR(45) NOT NULL, `createdAt` DA
TETIME NOT NULL, `contents` TEXT NOT NULL, `read` INTEGER NOT NULL, `participantNo` INTEGER, PRIMARY KEY (`no`), FOREIGN KEY (`participant
No`) REFERENCES `participant` (`no`) ON DELETE CASCADE ON UPDATE CASCADE) ENGINE=InnoDB;

Executing (default): CREATE TABLE IF NOT EXISTS `participant` (`no` INTEGER NOT NULL auto_increment , `role` VARCHAR(45) NOT NULL, `status
` ENUM('true', 'false') NOT NULL, `createdAt` DATETIME NOT NULL, `lastReadAt` DATETIME NOT NULL, `roomNo` INTEGER, `userNo` INTEGER, PRIMA
RY KEY (`no`), FOREIGN KEY (`roomNo`) REFERENCES `room` (`no`) ON DELETE CASCADE ON UPDATE CASCADE, FOREIGN KEY (`userNo`) REFERENCES `use
r` (`no`) ON DELETE CASCADE ON UPDATE CASCADE) ENGINE=InnoDB;
````
