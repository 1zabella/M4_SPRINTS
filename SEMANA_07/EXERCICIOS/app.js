const express = require('express');
const app = express();

const hostname = '127.0.0.1';
const port = 3000;

const bodyParser = require('body-parser');
const urlencodedParser = bodyParser.urlencoded({ extended: false })

app.use(express.static("EXERCICIOS"));

app.use(express.json());

app.listen(port, hostname, () => {
    console.log(`Page server running at http://${hostname}:${port}/`);
  });