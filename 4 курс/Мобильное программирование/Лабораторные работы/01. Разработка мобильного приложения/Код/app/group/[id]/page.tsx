import React from "react";
import GroupPageClient from "@/components/GroupPageClient";

interface GroupPageProps {
  params: Promise<{
    id: string;
  }>;
}

export default async function GroupPage({ params }: GroupPageProps) {
  const { id: groupCode } = await params;
  
  return <GroupPageClient groupCode={groupCode} />;
}
