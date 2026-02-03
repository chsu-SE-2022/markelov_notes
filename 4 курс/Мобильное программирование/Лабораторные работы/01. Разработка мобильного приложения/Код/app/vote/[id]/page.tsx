import React from "react";
import VotingPageClient from "@/components/VotingPageClient";

interface VotingPageProps {
  params: Promise<{
    id: string;
  }>;
}

export default async function VotingPage({ params }: VotingPageProps) {
  const { id: groupCode } = await params;
  // Нормализуем код группы (верхний регистр, без пробелов)
  const normalizedCode = groupCode?.toUpperCase().trim() || groupCode;
  return <VotingPageClient groupCode={normalizedCode} />;
}
