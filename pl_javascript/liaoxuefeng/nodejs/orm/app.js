const model = require('./model');

const
  Pet = model.Pet;
const User = model.User;

(async() => {
  const user = await User.create({
    name: 'John',
    gender: false,
    email: 'john-' + Date.now() + '@garfield.pet',
    passwd: 'hahaha'
  });
  console.log('created: ' + JSON.stringify(user));
  const cat = await Pet.create({
    ownerId: user.id,
    name: 'Garfield',
    gender: false,
    birth: '2007-07-07'
  });
  console.log('created: ' + JSON.stringify(cat));
  const dog = await Pet.create({
    ownerId: user.id,
    name: 'Odie',
    gender: false,
    birth: '2008-08-08'
  });
  console.log('created: ' + JSON.stringify(dog));
})();
