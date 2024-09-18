import sqlite3

class Database:
    def __init__(self) -> None:
        connection = sqlite3.connect("cache.db", check_same_thread=False)
        cursor = connection.cursor()

        cursor.execute("CREATE TABLE IF NOT EXISTS Cache (item1 text, item2 text, emoji text, combination text)")
        connection.commit()

        self.connection = connection
        self.cursor = cursor

    def get_all(self):
        self.cursor.execute("SELECT * FROM Cache")
        return self.cursor.fetchall()

    def get(self, item1, item2):
        self.cursor.execute(f"SELECT emoji, combination FROM Cache WHERE (item1 = '{item1}' AND item2 = '{item2}') OR (item1 = '{item2}' AND item2 = '{item1}')")
        fetched = self.cursor.fetchone()
        return None if fetched is None else (fetched[0], fetched[1])

    def set(self, item1, item2, emoji, combination):
        self.cursor.execute(f"INSERT INTO Cache VALUES('{item1}', '{item2}', '{emoji}', '{combination}')")
        self.commit()

    def check(self, item):
        self.cursor.execute(f"SELECT * from Cache WHERE item1 = '{item}' OR item2 = '{item}' or combination = '{item}'")
        fetched = self.cursor.fetchone()
        return fetched is not None and len(fetched) > 0

    # DANGEROUS METHODS - Hence not automatically comitting
    def clear(self):
        self.cursor.execute("DELETE FROM Cache")

    def drop(self):
        self.cursor.execute("DROP TABLE Cache")

    def commit(self):
        return self.connection.commit()


if __name__ == "__main__":
    db = Database()
    # db.set("Stone", "Stick", "🔨", "Hammer")
    # db.get("Stone", "Stick")
    # db.drop()
    db.clear()
    db.commit()
    # print(db.get_all())

    # Starter crafts
    db.set("Water", "Fire", "💨", "Steam")
    db.set("Water", "Wind", "🌊", "Wave")
    db.set("Water", "Earth", "🌱", "Plant")

    db.set("Fire", "Wind", "💨", "Smoke")
    db.set("Fire", "Earth", "🌋", "Lava")

    db.set("Wind", "Earth", "🌫️", "Dust")