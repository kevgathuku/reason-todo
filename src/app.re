[%bs.raw {|require('./app.css')|}];

/* type names and variable names must start with a small letter */
type item = {
  title: string,
  completed: bool,
};

type state = {
  /* this is a type w/ a type argument,
   * similar to List<Item> */
  items: list(item),
};

let component = ReasonReact.reducerComponent("TodoApp");

let str = ReasonReact.stringToElement;

/* underscores before names indicate unused variables. We name them for clarity */
let make = _children => {
  ...component,
  initialState: () => {
    items: [{title: "Write some things to do", completed: false}],
  },
  reducer: ((), _) => ReasonReact.NoUpdate,
  render: ({state: {items}}) => {
    let numItems = List.length(items);
    let itemsLabel =
      if (numItems > 1) {
        "items";
      } else {
        "item";
      };
    <div className="app">
      <div className="title"> (str("What to do")) </div>
      <div className="items"> (str("Nothing")) </div>
      <div className="footer">
        (str(string_of_int(numItems) ++ " " ++ itemsLabel))
      </div>
    </div>;
  },
};
