[%bs.raw {|require('./app.css')|}];

/* type names and variable names must start with a small letter */
type item = {
  id: int,
  title: string,
  completed: bool,
};

type state = {
  /* this is a type w/ a type argument,
   * similar to List<Item> */
  items: list(item),
};

let str = ReasonReact.stringToElement;

module TodoItem = {
  let component = ReasonReact.statelessComponent("TodoItem");
  /* ~item means a labelled arg */
  let make = (~item, ~onToggle, _children) => {
    ...component,
    render: _self =>
      <div className="item">
        <input
          _type="checkbox"
          checked=(Js.Boolean.to_js_boolean(item.completed))
          onChange=(_evt => onToggle())
        />
        (str(item.title))
      </div>,
  };
};

type action =
  | AddItem
  | ToggleItem(int);

/* Component template declaration must be **after** state and action declarations! */
let component = ReasonReact.reducerComponent("TodoApp");

let lastId = ref(0);

let newItem = () => {
  lastId := lastId^ + 1;
  {title: "Click a button", completed: true, id: lastId^};
};

let toggleItem = (items, id) =>
  List.map(
    item => item.id === id ? {...item, completed: ! item.completed} : item,
    items
  );

/* underscores before names indicate unused variables. We name them for clarity */
let make = _children => {
  ...component,
  initialState: () => {
    items: [{id: 0, title: "Write some things to do", completed: false}],
  },
  reducer: (action, {items}) =>
    switch (action) {
    | AddItem => ReasonReact.Update({items: [newItem(), ...items]})
    | ToggleItem(id) =>
      let items =
        List.map(
          item =>
            item.id === id ? {...item, completed: ! item.completed} : item,
          items
        );
      ReasonReact.Update({items: items});
    },
  render: self => {
    let {items} = self.state;
    let numItems = List.length(items);
    let itemsLabel =
      if (numItems > 1) {
        "items";
      } else {
        "item";
      };
    <div className="app">
      <div className="title">
        (str("What to do"))
        <button onClick=(_evt => self.send(AddItem))>
          (str("Add something"))
        </button>
      </div>
      <div className="items">
        (
          List.map(
            item => <TodoItem
              item
              key=(string_of_int(item.id))
              onToggle=(_evt => self.send(ToggleItem(item.id))) />,
            items,
          )
          |> Array.of_list
          |> ReasonReact.arrayToElement
        )
      </div>
      <div className="footer">
        (str(string_of_int(numItems) ++ " " ++ itemsLabel))
      </div>
    </div>;
  },
};
