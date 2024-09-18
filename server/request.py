from groq import Groq
import os
import json
import prompts

client = Groq(api_key=os.environ.get("GROQ_API_KEY"))

def craft(ob1, ob2, database):

    cached = database.get(ob1, ob2)
    if cached is not None:
        return {
            "combination": cached[1],
            "emoji": cached[0],
        }

    res = client.chat.completions.create(
        messages = [
            {
                "role": "system",
                "content": prompts.system_prompt,
            },
            {
                "role": "user",
                "content": prompts.user_prompt.format(item1=ob1, item2=ob2),
            }
        ],
        model = "llama-3.1-8b-instant",
    )

    content = res.choices[0].message.content
    content_json = None

    try:
        content_json = json.loads(content)
    except:
        return None
    
    emoji = content_json["emoji"]
    combination = content_json["combination"]
    
    database.set(ob1, ob2, emoji, combination)

    return content_json
    
if __name__ == "__main__":
    # database.clear()
    # database.commit()
    # print(database.get_all())
    # print(craft("Cement", "Gravel"))
    pass