[%bs.raw {|require('./app.css')|}];

[@bs.module] external logo : string = "./logo.svg";

let component = ReasonReact.statelessComponent("App");

let make = (_children) => {
  ...component,
  render: (_self) =>
    <div className="app">
      <div className="title"> (ReasonReact.stringToElement("What to do")) </div>
      <div className="items"> (ReasonReact.stringToElement("Nothing")) </div>
    </div>
};
