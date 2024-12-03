type input = {
  n : int; 
  t : int;
  lst : int list;
}

let int_list_of_string str = 
  String.split_on_char ' ' str 
  |> List.map int_of_string

let read_input () : input =
  let (n, t) = match int_list_of_string (read_line ()) with
    | n :: t :: _ -> (n, t)
    | _ -> raise Exit
  in 
  let list = int_list_of_string (read_line ()) in
  { n = n; t = t; lst = list; }

let rec take l n: 'a list = if n <= 0 then [] else match l with
  | x :: xs -> x :: (take xs (n - 1))
  | [] -> []

type state = {
  n: int;
  next: int array;
  visited: bool array;
}

let rec svn_case_visit (st: state) i =
  Array.set st.visited i true;
  match i with 
    | i when i < 0 || i > st.n -> print_endline "Out"
    | i when i = st.n - 1      -> print_endline "Done"
    | _ ->
      let j = Array.get st.next i in
      match Array.get st.visited j with
        | true -> print_endline "Cyclic"
        | false -> svn_case_visit st j

let seventh_case lst = 
  let st = { 
    n = List.length lst;
    next = List.to_seq lst |> Array.of_seq;
    visited = 
      Seq.repeat false |> 
      Seq.take (List.length lst) |> 
      Array.of_seq
  } in 
  svn_case_visit st 0

let () = 
  let { n = _; t; lst } = read_input () in
  match t with
    | 1 -> Printf.printf "%d\n" 7
    | 2 -> 
      let (x, y) = (List.nth lst 0, List.nth lst 1) in
      let str = match Int.compare x y with 
        | 0 -> "Equal"
        | n when n < 0 -> "Smaller"
        | _ -> "Bigger"
      in print_endline str
    | 3 -> 
      (take lst 3)
      |> List.sort Int.compare
      |> (fun l -> List.nth l 1)
      |> Printf.printf "%d\n"
    | 4 ->
      let sum = List.fold_left (fun acc x -> acc + x) 0 lst in
      Printf.printf "%d\n" sum
    | 5 ->
      let evens = List.filter (fun x -> x mod 2 == 0) in
      let sum = List.fold_left (fun acc x -> acc + x) 0 (evens lst) in
      Printf.printf "%d\n" sum
    | 6 -> 
      let codefora = int_of_char 'a' in
      lst |> List.map (fun x -> (x mod 26) + codefora)
      |> List.map char_of_int |> List.to_seq |> String.of_seq
      |> print_endline
    | 7 -> seventh_case lst
    | _ -> print_endline "unknown case"
