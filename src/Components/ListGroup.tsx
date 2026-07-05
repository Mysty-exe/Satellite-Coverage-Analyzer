import { useState } from "react";

interface Props 
{
    heading: string,
    items: string[],
}

function ListGroup({ heading, items }: Props)
{
    const [hoveringIndex, setHoveringIndex] = useState(-1);

  return (
    <>
    <h1>{heading}</h1>
    {items.length === 0 ? <p>No item found</p> : null}
    <ul className="list-group">
    {items.map( (item, index) => (
        <li key={index} className={hoveringIndex === index ? "list-group-item active" : "list-group-item"} aria-current="true" onMouseEnter={() => setHoveringIndex(index)} onMouseLeave={() => setHoveringIndex(-1)} >{item}</li>
        )
        )}
    </ul>
    </>
  )
}

export default ListGroup
