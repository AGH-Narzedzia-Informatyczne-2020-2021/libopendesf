<p align="center">
  <img src="https://i.imgur.com/JVpoc09.png" width=300>
</p>

The libopendesf-node project aims to provide easy to use bindings to [libopendesf](https://github.com/AGH-Narzedzia-Informatyczne/libopendesf).



# Installation
`npm install opendesf`

# Basic usage example

```javascript
const opendesf = require('opendesf');

const readers = await opendesf.listAllReaders();
console.log(readers);
```

# API
The project is currently in early development stages, thus the API is not considered stable. Breaking changes may occur anytime without prior notice.