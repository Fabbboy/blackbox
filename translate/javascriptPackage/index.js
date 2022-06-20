const SocketClient = require('socket.io-client');

/*

    "cdb" - create database
    "ddb" - delete database
    "cl" - create table
    "dl" - delete table
    "i" - insert key and value
    "g" - get value
    "rk" - remove key
*/
/*
translate into js

import socket

# connect to localhsot:7769
s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
s.connect(('localhost', 7769))
# send "hello"
s.send(b'rk-testSocket-hello-lol')
# receive "hello"
data = s.recv(1024)
print(data.decode('utf-8'))
# close socket
s.close()
*/


class BlackboxClient{
    constructor(ip) {
        this.ip = ip;
        this.port = 7769;
        this.socket = SocketClient.connect(this.ip + ':' + this.port);

    }
    send(message) {
        this.socket.send(message);
    }
    createDatabase(name) {
        this.send('cdb-' + name);
        this.disconnect();
    }
    deleteDatabase(name) {
        this.send('ddb-' + name);
        this.disconnect();
    }
    createTable(database, name) {
        this.send('cl-' + database + '-' + name);
        this.disconnect();
    }
    deleteTable(database, name) {
        this.send('dl-' + database + '-' + name);
        this.disconnect();
    }
    insert(database, table, key, value) {
        this.send('i-' + database + '-' + table + '-' + key + '-' + value);
        this.disconnect();
    }
    get(database, table, key) {
        this.send('g-' + database + '-' + table + '-' + key);
        //await message from server and return it
        return new Promise((resolve, reject) => {
            this.socket.onmessage = (event) => {
                resolve(event.data);
            }
        })
    }
    removeKey(database, table, key) {
        this.send('rk-' + database + '-' + table + '-' + key);
        this.disconnect();
    }
    disconnect() {
        this.socket.close();
    }
}

const client = new BlackboxClient("127.0.1.1");
client.send("cdb-test");
client.createDatabase('test');
client.createTable('test', 'test');