import streamlit as st
from typing import List, Tuple

from imports.db_handler import DBHandler


def _load_partial() -> List[Tuple]:
    db = DBHandler()
    return db.get_partial_details()


def _load_details(mal_id: int) -> List[Tuple]:
    db = DBHandler()
    return db.get_mal_info(mal_id)


def main() -> None:
    st.set_page_config(page_title="theZoo Streamlit", layout="wide")

    st.title("theZoo – Malware DB (Streamlit)")

    search = st.text_input("Filter by any field")

    rows = _load_partial()
    if search:
        q = search.lower().strip()
        if q:
            rows = [
                row for row in rows
                if any(q in str(value).lower() for value in row)
            ]

    if not rows:
        st.info("No results.")
        return

    table_rows = [
        {
            "ID": row[0],
            "Type": row[1],
            "Language": row[2],
            "Architecture": row[3],
            "Platform": row[4],
            "Name": row[5],
        }
        for row in rows
    ]

    st.dataframe(table_rows, hide_index=True, use_container_width=True)

    ids = [row["ID"] for row in table_rows]
    selected_id = st.selectbox("Select malware ID for details", ids)

    if selected_id is None:
        return

    details = _load_details(int(selected_id))
    if not details:
        st.warning("No additional metadata found for this entry.")
        return

    (
        mal_type,
        name,
        version,
        author,
        language,
        date,
        architecture,
        platform,
        tags,
    ) = details[0]

    st.subheader("Details")
    st.write({
        "Name": name,
        "Type": mal_type,
        "Version": version,
        "Author": author,
        "Language": language,
        "Date": date,
        "Architecture": architecture,
        "Platform": platform,
        "Tags": tags,
    })


if __name__ == "__main__":
    main()
